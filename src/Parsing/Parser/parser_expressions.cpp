#include "parser.h"
#include "../../Analysis/Structure/Wrappers/Generic/generic_extensions.h"

#include "../../Exceptions/exception_manager.h"
#include "../../Exceptions/Compilation/Parsing/invalid_token_exception.h"
#include "../../Exceptions/Compilation/Parsing/token_expected_exception.h"
#include "../../Exceptions/Compilation/Parsing/empty_expression_exception.h"
#include "../../Exceptions/Compilation/Parsing/generic_argument_exception.h"
#include "../../Exceptions/Compilation/Parsing/invalid_expression_exception.h"

#include "../../Lexing/Tokens/Enums/keyword_type.h"
#include "../../Lexing/Tokens/Factories/operator.h"

#include "../ParseNodes/Values/this_node.h"

#include "../ParseNodes/Statements/empty_node.h"

#include "../ParseNodes/Constants/constant_node.h"

#include "../ParseNodes/Expressions/Unary/unary_node.h"
#include "../ParseNodes/Expressions/dot_expression_node.h"
#include "../ParseNodes/Expressions/cast_expression_node.h"
#include "../ParseNodes/Expressions/Binary/binary_node.h"
#include "../ParseNodes/Expressions/Ternary/ternary_node.h"

#include "../ParseNodes/Types/Created/created_type_node.h"
#include "../ParseNodes/Types/BuiltIn/built_in_type_node.h"
#include "../ParseNodes/Types/Keyword/anonymous_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/func_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/list_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/tuple_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/array_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/action_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/nullable_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/dictionary_type_node.h"
#include "../ParseNodes/Values/null_node.h"

using namespace std;

using namespace Exceptions;

using namespace Tokens;
using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Types;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Values;
using namespace ParseNodes::Constants;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Expressions;

using namespace Analysis::Structure::Wrappers;

namespace Parsing
{
    const ParseNode* Parser::ParseEntity(const SeparatorKind breakSeparator)
    {
        stack<const Token*> tokens;
        stack<const ParseNode*> output;

        TokenType expected = TokenType::Constant | TokenType::Identifier | TokenType::Keyword;

        bool breakOut = false, subtract = false;
        for (; index < source->TokenCount(); index++)
        {
            auto current = Current();

            if (!MatchType(current, expected))
                breakOut = subtract = true;
            else
            {
                switch (current.Type())
                {
                    case TokenType::Constant:
                        {
                            output.push(new ConstantNode(current));
                            expected = TokenType::Separator;
                        }
                        break;
                    case TokenType::Identifier:
                        {
                            const auto identifier = new IdentifierNode(current);

                            if (MatchLookAhead(SyntaxKind::OpenBracket))
                            {
                                index++;
                                output.push(ParseFunctionCall(identifier));
                            }
                            else
                                output.push(identifier);

                            expected = TokenType::Separator;
                        }
                        break;
                    case TokenType::Separator:
                        {
                            if (MatchSeparator(current, breakSeparator))
                            {
                                breakOut = true;
                                break;
                            }

                            switch (current.Kind())
                            {
                                case SyntaxKind::Dot:
                                    {
                                        tokens.push(&current);
                                        expected = TokenType::Identifier;
                                    }
                                    break;
                                case SyntaxKind::BoxOpenBracket:
                                    {
                                        const auto top = output.top();
                                        output.pop();
                                        output.push(ParseIndexerExpression(top));
                                    }
                                    break;
                                default:
                                    breakOut = subtract = true;
                                    break;
                            }
                        }
                        break;
                    case TokenType::Keyword:
                        {
                            if (const auto keywordType = static_cast<KeywordType>(current.Metadata()); keywordType == KeywordType::Type)
                                output.push(ParseType());

                            else if (MatchToken(current, SyntaxKind::This))
                                output.push(new ThisNode(current));
                            else
                                breakOut = subtract = true;

                            expected = TokenType::Separator;
                        }
                        break;
                    default:
                        breakOut = subtract = true;
                        break;
                }
            }

            if (breakOut)
            {
                if (subtract)
                    index--;

                if (output.size() % 2 == tokens.size() % 2)
                {
                    ExceptionManager::Instance().AddChild(new TokenExpectedException(expected, Current(), source));
                    output.push(new InvalidNode(index));
                }

                ClearStack(tokens, output);
                break;
            }
        }

        if (!breakOut)
        {
            ExceptionManager::Instance().AddChild(new TokenExpectedException(breakSeparator, Current(), source));
            ClearStack(tokens, output);;
        }

        if (output.size() == 1)
        {
            const auto top = output.top();
            output.pop();
            return top;
        }

        const auto invalidNode = new InvalidNode(index);
        while (!output.empty())
        {
            const auto top = output.top();
            output.pop();
            invalidNode->AddChild(top);
        }

        ExceptionManager::Instance().AddChild(new InvalidExpressionException(Current(), source));
        return invalidNode;
    }

    const ParseNode* Parser::ParseExpression(const SeparatorKind breakSeparator)
    {
        stack<const Token*> tokens;
        stack<const ParseNode*> output;

        TokenType expected = TokenType::Constant | TokenType::Identifier | TokenType::UnaryOperator | TokenType::Keyword | TokenType::Separator;

        bool invalid = false, breakOut = false;
        for (; index < source->TokenCount(); index++)
        {
            const auto current = Current();

            if (!MatchType(current, expected))
                breakOut = invalid = true;
            else
            {
                switch (current.Type())
                {
                    case TokenType::Keyword:
                        {
                            switch (current.Kind())
                            {
                                case SyntaxKind::As:
                                    tokens.push(&current);
                                    break;
                                case SyntaxKind::This:
                                    output.push(ParseEntity(SeparatorKind::None));
                                    break;
                                case SyntaxKind::Input:
                                    output.push(ParsePrintCall());
                                    break;
                                case SyntaxKind::Invoke:
                                    output.push(ParseInvokeCall());
                                    break;
                                case SyntaxKind::FuncRef:
                                    output.push(ParseFuncRefCall());
                                    break;
                                case SyntaxKind::ToString:
                                    output.push(ParseToStringCall());
                                    break;
                                case SyntaxKind::Create:
                                    output.push(ParseConstructorCall());
                                    break;
                                case SyntaxKind::Null:
                                    output.push(new NullNode(current));
                                    break;
                                default:
                                    {
                                        if (const auto keywordType = static_cast<KeywordType>(current.Metadata()); keywordType == KeywordType::Type)
                                            output.push(ParseType());
                                        else
                                            invalid = breakOut = true;
                                    }
                                    break;
                            }

                            expected = TokenType::Separator | TokenType::Operator;
                        }
                        break;
                    case TokenType::Constant:
                    case TokenType::Identifier:
                        {
                            output.push(ParseEntity(SeparatorKind::Any));
                            expected = TokenType::Separator | TokenType::Operator;
                        }
                        break;
                    case TokenType::Separator:
                        {
                            if (MatchSeparator(current, breakSeparator))
                            {
                                breakOut = true;
                                break;
                            }

                            switch (current.Kind())
                            {
                                case SyntaxKind::OpenBracket:
                                    {
                                        output.push(ParseNonEmptyExpression(SeparatorKind::CloseBracket));
                                        expected = TokenType::Separator | TokenType::Operator;
                                    }
                                    break;
                                case SyntaxKind::QuestionMark:
                                    {
                                        if (output.empty())
                                        {
                                            ExceptionManager::Instance().AddChild(new EmptyExpressionException(Current(), source));
                                            output.push(new EmptyNode(Current()));
                                        }
                                        else
                                            ClearStack(tokens, output);

                                        const auto condition = output.top();
                                        output.pop();

                                        index++;
                                        const auto trueValue = ParseNonEmptyExpression(SeparatorKind::Colon);

                                        TryMatchToken(Current(), SyntaxKind::Colon, true);

                                        const auto falseValue = ParseNonEmptyExpression(breakSeparator);

                                        index--;
                                        output.push(new TernaryNode(condition, trueValue, falseValue));
                                        expected = TokenType::Separator | TokenType::Operator;
                                    }
                                    break;
                                default:
                                    invalid = breakOut = true;
                                    break;
                            }
                        }
                        break;
                    case TokenType::UnaryOperator:
                        {
                            if (!tokens.empty() && MatchType(*tokens.top(), TokenType::UnaryOperator))
                            {
                                invalid = breakOut = true;
                                break;
                            }

                            switch (const auto prev = source->TokenAt(index - 1); prev.Type())
                            {
                                case TokenType::Identifier:
                                    {
                                        tokens.push(&current);
                                        expected = TokenType::Separator | TokenType::BinaryOperator;
                                    }
                                    break;
                                case TokenType::BinaryOperator:
                                case TokenType::AssignmentOperator:
                                    {
                                        tokens.push(&current);
                                        expected = TokenType::Constant | TokenType::Identifier;

                                        if (MatchLookAhead(SyntaxKind::OpenBracket))
                                            expected = expected | TokenType::Separator;
                                    }
                                    break;
                                case TokenType::Separator:
                                    {
                                        if (MatchToken(prev, SyntaxKind::CloseBracket) || MatchToken(prev, SyntaxKind::BoxCloseBracket))
                                        {
                                            tokens.push(&current);
                                            expected = TokenType::Separator | TokenType::BinaryOperator;
                                        }
                                        else
                                        {
                                            tokens.push(&current);
                                            expected = TokenType::Constant | TokenType::Identifier;

                                            if (MatchLookAhead(SyntaxKind::OpenBracket))
                                                expected = expected | TokenType::Separator;
                                        }
                                    }
                                    break;
                                default:
                                    invalid = breakOut = true;
                                    break;
                            }
                        }
                        break;
                    case TokenType::AssignmentOperator:
                        {
                            tokens.push(&current);
                            expected = TokenType::Identifier | TokenType::Constant | TokenType::UnaryOperator | TokenType::Separator;
                        }
                        break;
                    case TokenType::BinaryOperator:
                        {
                            while (!tokens.empty())
                            {
                                const auto top = *tokens.top();
                                const auto topMetadata = Operator::DecodeMetadata(top);
                                const auto currentMetadata = Operator::DecodeMetadata(current);

                                if (std::get<1>(currentMetadata) < std::get<1>(topMetadata) || (std::get<1>(topMetadata)  == std::get<1>(currentMetadata) && !std::get<0>(currentMetadata)))
                                   break;

                                ClearStack(top, output);
                                tokens.pop();
                            }

                            tokens.push(&current);
                            expected = TokenType::Identifier | TokenType::Keyword | TokenType::Constant | TokenType::UnaryOperator;

                            if (MatchLookAhead(SyntaxKind::OpenBracket))
                                expected = expected | TokenType::Separator;
                        }
                        break;
                    default:
                        invalid = breakOut = true;
                        break;
                }
            }

            if (breakOut)
            {
                if (invalid)
                {
                    ExceptionManager::Instance().AddChild(new InvalidTokenException(Current(), source));
                    output.push(ParseInvalid(breakSeparator));
                }

                ClearStack(tokens, output);
            }
        }

        if (!breakOut)
        {
            ExceptionManager::Instance().AddChild(new TokenExpectedException(breakSeparator, Current(), source));
            ClearStack(tokens, output);
        }

        switch (output.size())
        {
            case 0:
                return new EmptyNode(Current());
            case 1:
                {
                    const auto top = output.top();
                    output.pop();
                    return top;
                }
            default:
                {
                    const auto invalidNode = new InvalidNode(index);
                    while (!output.empty())
                    {
                        const auto top = output.top();
                        output.pop();
                        invalidNode->AddChild(top);
                    }

                    ExceptionManager::Instance().AddChild(new InvalidExpressionException(Current(), source));
                    return invalidNode;
                }
        }
    }

    const ParseNode* Parser::ParseNonEmptyExpression(const SeparatorKind breakSeparator)
    {
        const auto expression = ParseExpression(breakSeparator);

        if (expression->NodeType() == NodeType::Empty)
        {
            ExceptionManager::Instance().AddChild(new EmptyExpressionException(Current(), source));
            const auto invalid = new InvalidNode(index);
            invalid->AddChild(expression);
            return invalid;
        }

        return expression;
    }

    void Parser::ClearStack(const Token& top, std::stack<const ParseNode*>& output)
    {
        if (MatchType(top, TokenType::UnaryOperator))
        {
            const auto node = new UnaryNode(top, output.top());
            output.pop();
            output.push(node);
        }

        const auto rhs = output.top();
        output.pop();
        const auto lhs = output.top();
        output.pop();

        if (MatchToken(top, SyntaxKind::Dot))
            output.push(new DotExpressionNode(lhs, rhs));
        if (MatchToken(top, SyntaxKind::As))
            output.push(new CastExpressionNode(lhs, rhs));

        output.push(new BinaryNode(top, lhs, rhs));
    }

    void Parser::ClearStack(std::stack<const Token*>& stack, std::stack<const ParseNode*>& output)
    {
        while (!stack.empty())
            ClearStack(*stack.top(), output);
    }

    const GenericNode* Parser::ParseGeneric()
    {
        TryMatchToken(Current(), SyntaxKind::LesserThan, true);

        const auto generic = new GenericNode(index - 1);
        while (index < source->TokenCount())
        {
            if (MatchType(Current(), TokenType::Keyword | TokenType::Identifier))
            {
                generic->AddChild(ParseType());
                index++;

                if (const auto current = Current(); MatchToken(current, SyntaxKind::Comma, true))
                    continue;
                else if (MatchToken(current, SyntaxKind::GreaterThan))
                    return generic;
            }

            ExceptionManager::Instance().AddChild(new InvalidTokenException(Current(), source));
            break;
        }

        generic->AddChild(ParseInvalid(SeparatorKind::Any));
        TryMatchToken(Current(), SyntaxKind::GreaterThan);
        return generic;
    }

    void Parser::ParseExpressionCollection(NodeCollection<ParseNode>* const collection, const SeparatorKind breakSeparator)
    {
        while (index < source->TokenCount())
        {
            const auto expression = ParseNonEmptyExpression(SeparatorKind::Comma | breakSeparator);
            collection->AddChild(expression);

            const auto current = Current();
            if (MatchToken(current, SyntaxKind::Comma, true))
                continue;
            if (MatchSeparator(current, breakSeparator))
                return;

            ExceptionManager::Instance().AddChild(new InvalidTokenException(current, source));
            break;
        }

        collection->AddChild(ParseInvalid(breakSeparator);
        TryMatchSeparator(Current(), breakSeparator);
    }

    const ScopeNode* Parser::ParseScopedExpression()
    {
        TryMatchToken(Current(), SyntaxKind::FlowerOpenBracket, true);

        const auto scope = new ScopeNode(index - 1);
        ParseExpressionCollection(scope, SeparatorKind::FlowerCloseBracket);

        return scope;
    }

    const IndexerExpressionNode* Parser::ParseIndexerExpression(const ParseNode* const operand)
    {
        TryMatchToken(Current(), SyntaxKind::BoxOpenBracket, true);

        const auto indexer = new IndexerExpressionNode(operand);
        ParseExpressionCollection(indexer, SeparatorKind::BoxCloseBracket);

        return indexer;
    }

    const ParseNode* Parser::ParseType()
    {
        switch (const auto current = Current(); current.Kind())
        {
            case SyntaxKind::Let:
                return new AnonymousTypeNode(current);
            case SyntaxKind::Int:
            case SyntaxKind::Long:
            case SyntaxKind::Short:
            case SyntaxKind::Float:
            case SyntaxKind::Double:
            case SyntaxKind::String:
            case SyntaxKind::Object:
            case SyntaxKind::Boolean:
            case SyntaxKind::Character:
                return new BuiltInTypeNode(current);
            case SyntaxKind::List:
                {
                    index++;
                    const auto generic = ParseGeneric();
                    if (generic->ChildCount() != 1)
                        ExceptionManager::Instance().AddChild(new GenericArgumentException(1, current, source));

                    return new ListTypeNode(current, generic);;
                }
            case SyntaxKind::Array:
                {
                    index++;
                    const auto generic = ParseGeneric();
                    if (generic->ChildCount() != 1)
                        ExceptionManager::Instance().AddChild(new GenericArgumentException(1, current, source));

                    return new ArrayTypeNode(current, generic);
                }
            case SyntaxKind::Tuple:
                {
                    index++;
                    const auto generic = ParseGeneric();
                    if (generic->ChildCount() > max_tuple_length)
                        ExceptionManager::Instance().AddChild(new GenericArgumentException(max_tuple_length, current, source));

                    return new TupleTypeNode(current, generic);
                }
            case SyntaxKind::Dictionary:
                {
                    index++;
                    const auto generic = ParseGeneric();
                    if (generic->ChildCount() != 2)
                        ExceptionManager::Instance().AddChild(new GenericArgumentException(2, current, source));

                    return new DictionaryTypeNode(current, generic);
                }
            case SyntaxKind::Func:
                {
                    index++;
                    const auto generic = ParseGeneric();
                    if (generic->ChildCount() > max_delegate_length)
                        ExceptionManager::Instance().AddChild(new GenericArgumentException(max_delegate_length, current, source));

                    return new FuncTypeNode(current, generic);
                }
            case SyntaxKind::Action:
                {
                    index++;
                    const auto generic = ParseGeneric();
                    if (generic->ChildCount() > max_delegate_length)
                        ExceptionManager::Instance().AddChild(new GenericArgumentException(max_delegate_length, current, source));

                    return new ActionTypeNode(current, generic);
                }
            case SyntaxKind::Nullable:
                {
                    index++;
                    const auto generic = ParseGeneric();
                    if (generic->ChildCount() != 1)
                        ExceptionManager::Instance().AddChild(new GenericArgumentException(1, current, source));

                    return new NullableTypeNode(current, generic);
                }
            default:
                {
                    if (MatchType(current, TokenType::Identifier))
                        return new CreatedTypeNode(new IdentifierNode(current));

                    return ParseInvalid(SeparatorKind::Any);
                }
        }
    }

    const ParseNode* Parser::CheckType(const ParseNode* const parsed) const
    {
        switch (parsed->NodeType())
        {
            case NodeType::Identifier:
                return new CreatedTypeNode(dynamic_cast<const IdentifierNode*>(parsed));
            case NodeType::FuncType:
            case NodeType::ListType:
            case NodeType::ArrayType:
            case NodeType::TupleType:
            case NodeType::ActionType:
            case NodeType::CreatedType:
            case NodeType::BuiltInType:
            case NodeType::NullableType:
            case NodeType::DictionaryType:
                return parsed;
            default:
                {
                    ExceptionManager::Instance().AddChild(new ParsingException("Type expected", Current(), source));;
                    const auto invalid = new InvalidNode(index);
                    invalid->AddChild(parsed);
                    return invalid;
                }
        }
    }

    const IdentifierNode* Parser::ParseIdentifier(const bool increment)
    {
        const auto current = Current();
        const auto identifier = new IdentifierNode(current);

        if (TryMatchType(current, TokenType::Identifier))
        {
            if (increment)
                index++;
        }
        else
            ExceptionManager::Instance().AddChild(new ParsingException("Identifier expected", current, source));

        return identifier;
    }
}

