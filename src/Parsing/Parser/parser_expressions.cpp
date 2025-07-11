#include "parser.h"

#include <stack>

#include "../ParseNodes/Values/this_node.h"
#include "../ParseNodes/Values/null_node.h"

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
#include "../ParseNodes/Types/Keyword/void_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/func_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/list_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/tuple_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/array_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/action_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/nullable_type_node.h"
#include "../ParseNodes/Types/Keyword/Generic/dictionary_type_node.h"

#include "../../Exceptions/exception_manager.h"
#include "../../Exceptions/Compilation/Parsing/invalid_token_exception.h"
#include "../../Exceptions/Compilation/Parsing/token_expected_exception.h"
#include "../../Exceptions/Compilation/Parsing/empty_expression_exception.h"
#include "../../Exceptions/Compilation/Parsing/generic_argument_exception.h"
#include "../../Exceptions/Compilation/Parsing/invalid_expression_exception.h"

#include "../../Lexing/Tokens/Enums/keyword_type.h"
#include "../../Lexing/Tokens/Factories/operator.h"

#include "../../Analysis/Structure/Wrappers/Generic/generic_extensions.h"

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
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Wrappers;

namespace Parsing
{
    const IParseNode* Parser::ParseEntity(const SeparatorKind breakSeparator)
    {
        std::stack<const Token*> tokens;
        std::stack<const IParseNode*> output;

        TokenType expected = TokenType::Constant | TokenType::Identifier | TokenType::Keyword;

        bool breakOut = false, subtract = false;
        for (; index < source->TokenCount(); index++)
        {
            const auto& current = Current();

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
                    ExceptionManager::PushException(TokenExpectedException(expected, Current(), source));
                    output.push(new InvalidNode(Current()));
                }

                ClearStack(tokens, output);
                break;
            }
        }

        if (!breakOut)
        {
            ExceptionManager::PushException(TokenExpectedException(breakSeparator, Current(), source));
            ClearStack(tokens, output);;
        }

        if (output.size() == 1)
        {
            const auto top = output.top();
            output.pop();
            return top;
        }

        const auto invalidNode = new InvalidNode(Current());
        while (!output.empty())
        {
            const auto top = output.top();
            output.pop();
            invalidNode->AddChild(top);
        }

        ExceptionManager::PushException(InvalidExpressionException(Current(), source));
        return invalidNode;
    }

    const IParseNode* Parser::ParseExpression(const SeparatorKind breakSeparator)
    {
        std::stack<const Token*> tokens;
        std::stack<const IParseNode*> output;

        TokenType expected = TokenType::Constant | TokenType::Identifier | TokenType::UnaryOperator | TokenType::Keyword | TokenType::Separator;

        bool invalid = false, breakOut = false;
        for (; index < source->TokenCount(); index++)
        {
            const auto& current = Current();

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
                                case SyntaxKind::Ref:
                                    output.push(ParseRefCall());
                                    break;
                                case SyntaxKind::Copy:
                                    output.push(ParseCopyCall());
                                    break;
                                case SyntaxKind::This:
                                    output.push(ParseEntity(SeparatorKind::None));
                                    break;
                                case SyntaxKind::Input:
                                    output.push(ParseInputCall());
                                    break;
                                case SyntaxKind::Format:
                                    output.push(ParseFormatCall());
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
                                            output.push(ParseEntity(SeparatorKind::Any));
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
                                        index++;
                                        output.push(ParseNonEmptyExpression(SeparatorKind::CloseBracket));
                                        expected = TokenType::Separator | TokenType::Operator;
                                    }
                                    break;
                                case SyntaxKind::QuestionMark:
                                    {
                                        if (output.empty())
                                        {
                                            ExceptionManager::PushException(EmptyExpressionException(Current(), source));
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
                                        output.push(new TernaryNode(condition, trueValue, falseValue, current));
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

                                        if (MatchLookAhead(SyntaxKind::OpenBracket))
                                            expected = TokenType::Separator;
                                        else
                                            expected = TokenType::Constant | TokenType::Identifier;
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

                                            if (MatchLookAhead(SyntaxKind::OpenBracket))
                                                expected = TokenType::Separator;
                                            else
                                                expected = TokenType::Constant | TokenType::Identifier;
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
                                const auto& top = *tokens.top();
                                const auto topMetadata = Operator::DecodeMetadata(top);
                                const auto currentMetadata = Operator::DecodeMetadata(current);

                                if (std::get<1>(currentMetadata) < std::get<1>(topMetadata) || (std::get<1>(topMetadata)  == std::get<1>(currentMetadata) && !std::get<0>(currentMetadata)))
                                   break;

                                ClearStack(top, output);
                                tokens.pop();
                            }

                            tokens.push(&current);

                            if (MatchLookAhead(SyntaxKind::OpenBracket))
                                expected = TokenType::Separator;
                            else
                                expected = TokenType::Identifier | TokenType::Keyword | TokenType::Constant | TokenType::UnaryOperator;
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
                    ExceptionManager::PushException(InvalidTokenException(Current(), source));
                    output.push(ParseInvalid(breakSeparator));
                }

                ClearStack(tokens, output);
                break;
            }
        }

        if (!breakOut)
        {
            ExceptionManager::PushException(TokenExpectedException(breakSeparator, Current(), source));
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
                    const auto invalidNode = new InvalidNode(Current());
                    while (!output.empty())
                    {
                        const auto top = output.top();
                        output.pop();
                        invalidNode->AddChild(top);
                    }

                    ExceptionManager::PushException(InvalidExpressionException(Current(), source));
                    return invalidNode;
                }
        }
    }

    const IParseNode* Parser::ParseNonEmptyExpression(const SeparatorKind breakSeparator)
    {
        const auto expression = ParseExpression(breakSeparator);

        if (expression->NodeType() == NodeType::Empty)
        {
            ExceptionManager::PushException(EmptyExpressionException(Current(), source));
            const auto invalid = new InvalidNode(Current());
            invalid->AddChild(expression);
            return invalid;
        }

        return expression;
    }

    void Parser::ClearStack(const Token& top, std::stack<const IParseNode*>& output)
    {
        if (MatchType(top, TokenType::UnaryOperator))
        {
            const auto node = new UnaryNode(top, output.top());
            output.pop();
            output.push(node);
            return;
        }

        const auto rhs = output.top();
        output.pop();
        const auto lhs = output.top();
        output.pop();

        if (MatchToken(top, SyntaxKind::Dot))
            output.push(new DotExpressionNode(lhs, rhs, top));
        else if (MatchToken(top, SyntaxKind::As))
            output.push(new CastExpressionNode(lhs, rhs, top));
        else
            output.push(new BinaryNode(top, lhs, rhs));
    }

    void Parser::ClearStack(std::stack<const Token*>& stack, std::stack<const IParseNode*>& output)
    {
        while (!stack.empty())
        {
            const auto& top = *stack.top();

            ClearStack(top, output);
            stack.pop();
        }
    }

    void Parser::ParseGeneric(DynamicNodeCollection* const generic)
    {
        TryMatchToken(Current(), SyntaxKind::LesserThan, true);

        while (index < source->TokenCount())
        {
            if (MatchType(Current(), TokenType::Keyword | TokenType::Identifier))
            {
                generic->AddChild(ParseType());
                index++;

                if (const auto& current = Current(); MatchToken(current, SyntaxKind::Comma, true))
                    continue;
                else if (MatchToken(current, SyntaxKind::GreaterThan))
                    return;
            }

            ExceptionManager::PushException(InvalidTokenException(Current(), source));
            break;
        }

        generic->AddChild(ParseInvalid(SeparatorKind::Any));
        TryMatchToken(Current(), SyntaxKind::GreaterThan);
    }

    void Parser::ParseExpressionCollection(DynamicNodeCollection* const collection, const SeparatorKind breakSeparator)
    {
        while (index < source->TokenCount())
        {
            const auto expression = ParseNonEmptyExpression(SeparatorKind::Comma | breakSeparator);
            collection->AddChild(expression);

            const auto& current = Current();
            if (MatchToken(current, SyntaxKind::Comma, true))
                continue;
            if (MatchSeparator(current, breakSeparator))
                return;

            ExceptionManager::PushException(InvalidTokenException(current, source));
            break;
        }

        collection->AddChild(ParseInvalid(breakSeparator));
        TryMatchSeparator(Current(), breakSeparator);
    }

    const IndexerExpressionNode* Parser::ParseIndexerExpression(const IParseNode* const operand)
    {
        TryMatchToken(Current(), SyntaxKind::BoxOpenBracket, true);

        const auto indexer = new IndexerExpressionNode(operand);
        ParseExpressionCollection(indexer, SeparatorKind::BoxCloseBracket);

        return indexer;
    }

    const IParseNode* Parser::ParseType()
    {
        switch (const auto& current = Current(); current.Kind())
        {
            case SyntaxKind::Let:
                return new AnonymousTypeNode(current);
            case SyntaxKind::Void:
                return new VoidTypeNode(current);
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
                    const auto list =new ListTypeNode(current);
                    ParseGeneric(list);

                    if (list->ChildCount() != 1)
                        ExceptionManager::PushException(GenericArgumentException(1, current, source));

                    return list;
                }
            case SyntaxKind::Array:
                {
                    index++;
                    const auto array = new ArrayTypeNode(current);
                    ParseGeneric(array);

                    if (array->ChildCount() != 1)
                        ExceptionManager::PushException(GenericArgumentException(1, current, source));

                    return array;
                }
            case SyntaxKind::Tuple:
                {
                    index++;
                    const auto tuple = new TupleTypeNode(current);
                    ParseGeneric(tuple);

                    if (tuple->ChildCount() > max_tuple_length)
                        ExceptionManager::PushException(GenericArgumentException(max_tuple_length, current, source));

                    return tuple;
                }
            case SyntaxKind::Dictionary:
                {
                    index++;
                    const auto dictionary = new DictionaryTypeNode(current);
                    ParseGeneric(dictionary);
                    if (dictionary->ChildCount() != 2)
                        ExceptionManager::PushException(GenericArgumentException(2, current, source));

                    return dictionary;
                }
            case SyntaxKind::Func:
                {
                    index++;
                    const auto func = new FuncTypeNode(current);
                    ParseGeneric(func);
                    if (func->ChildCount() > max_delegate_length)
                        ExceptionManager::PushException(GenericArgumentException(max_delegate_length, current, source));

                    return func;
                }
            case SyntaxKind::Action:
                {
                    index++;
                    const auto action = new ActionTypeNode(current);

                    if (MatchToken(Current(), SyntaxKind::LesserThan))
                    {
                        ParseGeneric(action);
                        if (action->ChildCount() > max_delegate_length)
                            ExceptionManager::PushException(GenericArgumentException(max_delegate_length, current, source));
                    }

                    return action;
                }
            case SyntaxKind::Nullable:
                {
                    index++;
                    const auto nullable = new NullableTypeNode(current);
                    ParseGeneric(nullable);
                    if (nullable->ChildCount() != 1)
                        ExceptionManager::PushException(GenericArgumentException(1, current, source));

                    return nullable;
                }
            default:
                {
                    if (MatchType(current, TokenType::Identifier))
                        return new CreatedTypeNode(new IdentifierNode(current));

                    return ParseInvalid(SeparatorKind::Any);
                }
        }
    }

    const IParseNode* Parser::CheckType(const IParseNode* const parsed) const
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
                    ExceptionManager::PushException(ParsingException("Type expected", Current(), source));;
                    const auto invalid = new InvalidNode(Current());
                    invalid->AddChild(parsed);
                    return invalid;
                }
        }
    }

    const IdentifierNode* Parser::ParseIdentifier(const bool increment)
    {
        const auto& current = Current();
        const auto identifier = new IdentifierNode(current);

        if (TryMatchType(current, TokenType::Identifier))
        {
            if (increment)
                index++;
        }
        else
            ExceptionManager::PushException(ParsingException("Identifier expected", current, source));

        return identifier;
    }
}

