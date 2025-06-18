#include "parser.h"

#include "../../Exceptions/exception_manager.h"
#include "../../Exceptions/Compilation/Parsing/invalid_token_exception.h"
#include "../../Exceptions/Compilation/Parsing/token_expected_exception.h"
#include "../../Exceptions/Compilation/Parsing/function_argument_exception.h"

#include "../ParseNodes/Statements/initialisation_node.h"

#include "../ParseNodes/Properties/base_indexer_node.h"
#include "../ParseNodes/Properties/assigned_property_node.h"

#include "../ParseNodes/Functions/Creation/explicit_cast_node.h"
#include "../ParseNodes/Functions/Creation/implicit_cast_node.h"
#include "../ParseNodes/Functions/Calling/constructor_call_node.h"
#include "../ParseNodes/Functions/Creation/function_creation_node.h"
#include "../ParseNodes/Functions/Creation/operator_overload_node.h"
#include "../ParseNodes/Functions/Calling/collection_construction_call_node.h"
#include "../ParseNodes/Statements/empty_node.h"

using namespace Exceptions;

using namespace Tokens;
using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Values;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Describers;
using namespace ParseNodes::Properties;
using namespace ParseNodes::Core::Interfaces;
using namespace ParseNodes::Functions::Calling;
using namespace ParseNodes::Functions::Creation;

namespace Parsing
{
    const IParseNode* Parser::ParseGet(const DescriberNode* const describer)
    {
        const auto& keyword = Current();
        index++;

        if (MatchToken(Current(), SyntaxKind::Semicolon))
            return new GetNode(describer, new EmptyNode(source->TokenAt(index - 1)), keyword);

        return new GetNode(describer, ParseScope(), keyword);
    }

    const IParseNode* Parser::ParseSet(const DescriberNode* const describer)
    {
        const auto& keyword = Current();
        index++;

        if (MatchToken(Current(), SyntaxKind::Semicolon))
            return new SetNode(describer, new EmptyNode(source->TokenAt(index - 1)), keyword);

        return new SetNode(describer, ParseScope(), keyword);
    }

    const IParseNode* Parser::ParseProperty(const DescriberNode* const describer, const IParseNode* const type, const IdentifierNode* const identifier)
    {
        TryMatchToken(Current(), SyntaxKind::FlowerOpenBracket, true);

        const auto result = ParseAccessors();
        TryMatchToken(Current(), SyntaxKind::FlowerCloseBracket, true);

        if (MatchToken(Current(), SyntaxKind::Equals, true))
        {
            const auto value = ParseNonEmptyExpression(SeparatorKind::Semicolon);
            return new AssignedPropertyNode(describer, type, identifier, std::get<0>(result), std::get<1>(result), value);;
        }

        return new BasePropertyNode(describer, type, identifier, std::get<0>(result), std::get<1>(result));
    }

    const IParseNode* Parser::ParseIndexer(const DescriberNode* const describer)
    {
        const auto& keyword = Current();
        index++;

        const auto type = ParseType();
        index++;

        const auto parameters = ParseFunctionParameters();
        index++;

        TryMatchToken(Current(), SyntaxKind::FlowerOpenBracket, true);

        const auto result = ParseAccessors();

        TryMatchToken(Current(), SyntaxKind::FlowerCloseBracket);
        return new BaseIndexerNode(describer, type, parameters, std::get<0>(result), std::get<1>(result), keyword);
    }

    std::tuple<const IParseNode*, const IParseNode*> Parser::ParseAccessors()
    {
        const auto& firstToken = Current();

        const auto first = ParseStatement();
        switch (first->NodeType())
        {
            case NodeType::Get:
                index++;
                break;
            case NodeType::Set:
                {
                    index++;
                    TryMatchToken(Current(), SyntaxKind::FlowerCloseBracket);

                    return { nullptr, first };
                }
            default:
                {
                    ExceptionManager::Instance().AddChild(new TokenExpectedException(SyntaxKind::Get, firstToken, source));

                    const auto invalid = ParseInvalid(SeparatorKind::FlowerCloseBracket);
                    invalid->AddChild(first);

                    return { invalid, nullptr };
                }
        }

        const auto& secondToken = Current();
        if (MatchToken(secondToken, SyntaxKind::FlowerCloseBracket))
            return { first, nullptr };

        switch (const auto& second = ParseStatement(); second->NodeType())
        {
            case NodeType::Set:
                {
                    index++;
                    TryMatchToken(Current(), SyntaxKind::FlowerCloseBracket);

                    return { first, second };
                }
            default:
                {
                    ExceptionManager::Instance().AddChild(new TokenExpectedException(SyntaxKind::Set, secondToken, source));

                    const auto invalid = ParseInvalid(SeparatorKind::FlowerCloseBracket);
                    invalid->AddChild(second);

                    return { first, invalid };
                }
        }
    }

    const MultipleDeclarationNode* Parser::ParseFunctionParameters()
    {
        const auto parameters = new MultipleDeclarationNode(source->TokenAt(index));
        if (!TryMatchToken(Current(), SyntaxKind::OpenBracket, true))
        {
            const auto invalid = ParseInvalid(SeparatorKind::CloseBracket | SeparatorKind::FlowerOpenBracket);
            parameters->AddChild(invalid);
            return parameters;
        }

        if (MatchToken(Current(), SyntaxKind::CloseBracket))
            return parameters;

        while (index < source->TokenCount())
        {
            const DescriberNode* describer;
            if (MatchToken(Current(), SyntaxKind::BoxOpenBracket))
            {
                describer = ParseDescriber();
                index++;
            }
            else
                describer = new DescriberNode(Current());

            const auto type = ParseType();
            index++;

            TryMatchToken(Current(), SyntaxKind::Colon, true);

            const auto identifier = ParseIdentifier();
            index++;

            const auto& current = Current();
            parameters->AddChild(new DeclarationNode(describer, type, identifier, current));
            if (MatchToken(current, SyntaxKind::Comma, true))
                continue;
            if (MatchToken(current, SyntaxKind::CloseBracket))
                break;

            ExceptionManager::Instance().AddChild(new InvalidTokenException(current, source));

            parameters->AddChild(new InitialisationNode(describer, type, identifier, ParseInvalid(SeparatorKind::CloseBracket), Current()));
            TryMatchToken(Current(), SyntaxKind::CloseBracket);
            break;
        }

        return parameters;
    }

    void Parser::ParseFunctionArguments(DynamicNodeCollection* const function)
    {
        TryMatchToken(Current(), SyntaxKind::OpenBracket, true);

        if (!MatchToken(Current(), SyntaxKind::CloseBracket))
             ParseExpressionCollection(function, SeparatorKind::CloseBracket);;
    }

    const IParseNode* Parser::ParseConstructorCall()
    {
        const auto& keyword = Current();
        index++;

        const auto type = ParseType();
        index++;

        switch (type->NodeType())
        {
            case NodeType::ListType:
            case NodeType::ArrayType:
                {
                    if (MatchToken(Current(), SyntaxKind::FlowerOpenBracket, true))
                    {
                        const auto collectionConstructorNode = new CollectionConstructorCallNode(type, keyword);
                        ParseExpressionCollection(collectionConstructorNode, SeparatorKind::FlowerCloseBracket);

                        return collectionConstructorNode;
                    }
                }
                break;
            default:
                break;
        }

        const auto constructor = new ConstructorCallNode(type, keyword);
        ParseFunctionArguments(constructor);
        return constructor;
    }

    const FunctionCallNode* Parser::ParseFunctionCall(const IdentifierNode* const identifier)
    {
        const auto functionCall = new FunctionCallNode(identifier);

        ParseFunctionArguments(functionCall);
        return functionCall;
    }

    const IParseNode* Parser::ParseFunction(const DescriberNode* const describer, const IParseNode* const type)
    {
        const auto identifier = ParseIdentifier(true);

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new FunctionCreationNode(describer, type, identifier, parameters, body);
    }

    const IParseNode* Parser::ParseConstructor(const DescriberNode* const describer)
    {
        const auto& keyword = Current();
        index++;

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new ConstructorCreationNode(describer, parameters, body, keyword);
    }

    const IParseNode* Parser::ParseExplicitCast(const DescriberNode* const describer)
    {
        const auto& keyword = Current();
        index++;

        const auto type = ParseType();
        index++;

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new ExplicitCastNode(describer, type, parameters, body, keyword);
    }

    const IParseNode* Parser::ParseImplicitCast(const DescriberNode* const describer)
    {
        const auto& keyword = Current();
        index++;

        const auto type = ParseType();
        index++;

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new ImplicitCastNode(describer, type, parameters, body, keyword);
    }

    const IParseNode* Parser::ParseOperatorOverload(const DescriberNode* const describer)
    {
        index++;

        const auto type = ParseType();
        index++;

        const auto& baseOperator =  TryMatchType(Current(), TokenType::Operator, true) ? source->TokenAt(index - 1) : Current();

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new OperatorOverloadNode(describer, type, baseOperator, parameters, body);
    }

    const PrintNode* Parser::ParsePrintCall()
    {
        const auto& keyword = Current();
        const auto print = new PrintNode(keyword);;
        index++;

        ParseFunctionArguments(print);
        if (print->ChildCount() != 1)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        index++;
        return print;
    }

    const PrintlnNode* Parser::ParsePrintlnCall()
    {
        const auto& keyword = Current();
        const auto print = new PrintlnNode(keyword);;
        index++;

        ParseFunctionArguments(print);
        if (print->ChildCount() != 1)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        return print;
    }

    const InputNode* Parser::ParseInputCall()
    {
        const auto& keyword = Current();
        const auto input = new InputNode(Current());;
        index++;

        ParseFunctionArguments(input);
        if (input->ChildCount() > 0)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(0, keyword, source));

        return input;
    }

    const FormatNode* Parser::ParseFormatCall()
    {
        const auto& keyword = Current();
        const auto format = new FormatNode(Current());;
        index++;

        ParseFunctionArguments(format);
        if (format->ChildCount() < 1)
            ExceptionManager::Instance().AddChild(new MinimumFunctionArgumentException(1, keyword, source));

        return format;
    }

    const InvokeNode* Parser::ParseInvokeCall()
    {
        const auto& keyword = Current();
        const auto invoke = new InvokeNode(Current());;
        index++;

        ParseFunctionArguments(invoke);
        if (invoke->ChildCount() < 1)
            ExceptionManager::Instance().AddChild(new MinimumFunctionArgumentException(1, keyword, source));

        return invoke;
    }

    const FuncRefNode* Parser::ParseFuncRefCall()
    {
        const auto& keyword = Current();
        const auto funcRef = new FuncRefNode(keyword);
        index++;

        if (MatchToken(Current(), SyntaxKind::LesserThan))
        {
            ParseGeneric(funcRef);
            if (Current().Kind() == SyntaxKind::GreaterThan)
                index++;
        }

        const auto genericLength = funcRef->ChildCount();
        ParseFunctionArguments(funcRef);

        if (funcRef->ChildCount() - genericLength != 2)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(2, keyword, source));

        return funcRef;
    }

    const ToStringNode* Parser::ParseToStringCall()
    {
        const auto& keyword = Current();
        const auto toString = new ToStringNode(Current());;
        index++;

        ParseFunctionArguments(toString);
        if (toString->ChildCount() != 1)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        return toString;
    }

    const RefCallNode* Parser::ParseRefCall()
    {
        const auto& keyword = Current();
        const auto ref = new RefCallNode(keyword);;
        index++;

        ParseFunctionArguments(ref);
        if (ref->ChildCount() != 1)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        return ref;
    }

    const CopyCallNode* Parser::ParseCopyCall()
    {
        const auto& keyword = Current();
        const auto copy = new CopyCallNode(keyword);;
        index++;

        ParseFunctionArguments(copy);
        if (copy->ChildCount() != 1)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        return copy;
    }
}