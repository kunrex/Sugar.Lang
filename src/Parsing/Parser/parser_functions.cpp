#include "parser.h"

#include "../../Exceptions/exception_manager.h"
#include "../ParseNodes/Statements/initialisation_node.h"
#include "../ParseNodes/Properties/assigned_property_node.h"
#include "../../Exceptions/Compilation/Parsing/invalid_token_exception.h"
#include "../../Exceptions/Compilation/Parsing/token_expected_exception.h"
#include "../../Exceptions/Compilation/Parsing/function_argument_exception.h"
#include "../ParseNodes/Functions/Calling/collection_construction_call_node.h"

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
using namespace ParseNodes::Functions::Calling;
using namespace ParseNodes::Functions::Creation;

namespace Parsing
{
    const BasePropertyNode* Parser::ParseProperty(const DescriberNode* const describer, const ParseNode* const type, const IdentifierNode* const identifier)
    {
        TryMatchToken(Current(), SyntaxKind::FlowerOpenBracket, true);

        const GetNode* get = nullptr;
        const SetNode* set = nullptr;

        auto desc = MatchToken(Current(), SyntaxKind::BoxOpenBracket) ? ParseDescriber() : new DescriberNode(index);
        if (MatchToken(Current(), SyntaxKind::Get))
        {
            const auto current = Current();
            index++;

            const auto body = ParseScope();
            index++;

            get = new GetNode(desc, body, current);
            index++;
        }

        desc = MatchToken(Current(), SyntaxKind::BoxOpenBracket) ? ParseDescriber() : new DescriberNode(index);
        if (MatchToken(Current(), SyntaxKind::Set))
        {
            const auto current = Current();
            index++;

            const auto body = ParseScope();
            index++;

            set = new SetNode(desc, body, current);
            index++;
        }

        TryMatchToken(Current(), SyntaxKind::FlowerCloseBracket, true);
        if (get == nullptr && set == nullptr)
            ExceptionManager::Instance().AddChild(new TokenExpectedException(SyntaxKind::Get, Current(), source));

        if (MatchToken(Current(), SyntaxKind::Equals, true))
        {
            const auto value = ParseNonEmptyExpression(SeparatorKind::Semicolon);
            return new AssignedPropertyNode(describer, type, identifier, get, set, value);;
        }

        return new BasePropertyNode(describer, type, identifier, get, set);
    }

    const BaseIndexerNode* Parser::ParseIndexer(const DescriberNode* const describer)
    {
        const auto keyword = Current();
        index++;

        const auto type = ParseType();
        index++;

        const auto parameters = ParseFunctionParameters();
        index++;

        TryMatchToken(Current(), SyntaxKind::FlowerOpenBracket, true);

        const GetNode* get = nullptr;
        const SetNode* set = nullptr;

        auto desc = MatchToken(Current(), SyntaxKind::BoxOpenBracket) ? ParseDescriber() : new DescriberNode(index);
        if (MatchToken(Current(), SyntaxKind::Get))
        {
            const auto current = Current();
            index++;

            const auto body = ParseScope();
            index++;

            get = new GetNode(desc, body, current);
            index++;
        }

        desc = MatchToken(Current(), SyntaxKind::BoxOpenBracket) ? ParseDescriber() : new DescriberNode(index);
        if (MatchToken(Current(), SyntaxKind::Set))
        {
            const auto current = Current();
            index++;

            const auto body = ParseScope();
            index++;

            set = new SetNode(desc, body, current);
            index++;
        }

        TryMatchToken(Current(), SyntaxKind::FlowerCloseBracket);
        if (get == nullptr && set == nullptr)
            ExceptionManager::Instance().AddChild(new TokenExpectedException(SyntaxKind::Get, Current(), source));

        return new BaseIndexerNode(describer, type, parameters, get, set, keyword);
    }

    const CompoundDeclarationNode* Parser::ParseFunctionParameters()
    {
        TryMatchToken(Current(), SyntaxKind::OpenBracket, true);

        const auto parameters = new CompoundDeclarationNode();

        while (index < source->TokenCount())
        {
            const DescriberNode* describer;
            if (MatchToken(Current(), SyntaxKind::BoxOpenBracket))
            {
                describer = ParseDescriber();
                index++;
            }
            else
                describer = new DescriberNode(index);

            const auto type = ParseType();
            index++;

            TryMatchToken(Current(), SyntaxKind::Colon, true);

            const auto identifier = ParseIdentifier();
            index++;

            const auto current = Current();
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

    void Parser::ParseFunctionArguments(NodeCollection<ParseNode>* const function)
    {
        TryMatchToken(Current(), SyntaxKind::OpenBracket, true);
        ParseExpressionCollection(function, SeparatorKind::CloseBracket);
    }

    const ParseNode* Parser::ParseConstructorCall()
    {
        const auto keyword = Current();
        index++;

        const auto type = ParseType();
        index++;

        switch (type->NodeType())
        {
            case NodeType::ListType:
            case NodeType::ArrayType:
                {
                    if (MatchToken(Current(), SyntaxKind::FlowerOpenBracket))
                        return new CollectionConstructorCallNode(type, ParseScopedExpression());
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

    const FunctionCreationNode* Parser::ParseFunction(const DescriberNode* const describer, const ParseNode* const type)
    {
        const auto identifier = ParseIdentifier(true);

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new FunctionCreationNode(describer, type, identifier, parameters, body);
    }

    const ConstructorCreationNode* Parser::ParseConstructor(const DescriberNode* const describer)
    {
        const auto keyword = Current();
        index++;

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new ConstructorCreationNode(describer, parameters, body, keyword);
    }

    const ExplicitCastNode* Parser::ParseExplicitCast(const DescriberNode* const describer)
    {
        const auto keyword = Current();
        index++;

        const auto type = ParseType();
        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new ExplicitCastNode(describer, type, parameters, body, keyword);
    }

    const ImplicitCastNode* Parser::ParseImplicitCast(const DescriberNode* const describer)
    {
        const auto keyword = Current();
        index++;

        const auto type = ParseType();
        index++;

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new ImplicitCastNode(describer, type, parameters, body, keyword);
    }

    const OperatorOverloadNode* Parser::ParseOperatorOverload(const DescriberNode* const describer)
    {
        const auto keyword = Current();
        index++;

        const auto type = ParseType();
        index++;

        TryMatchType(Current(), TokenType::Operator);
        const auto baseOperator = Current();
        index++;

        const auto parameters = ParseFunctionParameters();
        index++;

        const auto body = ParseScope();
        return new OperatorOverloadNode(describer, type, baseOperator, parameters, body, keyword);;
    }

    const PrintNode* Parser::ParsePrintCall()
    {
        const auto keyword = Current();
        const auto print = new PrintNode(keyword);;
        index++;

        ParseFunctionArguments(print);
        if (print->ChildCount() != 1)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        return print;
    }

    const PrintlnNode* Parser::ParsePrintlnCall()
    {
        const auto keyword = Current();
        const auto print = new PrintlnNode(keyword);;
        index++;

        ParseFunctionArguments(print);
        if (print->ChildCount() != 1)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        return print;
    }

    const InputNode* Parser::ParseInputCall()
    {
        const auto keyword = Current();
        const auto input = new InputNode(Current());;
        index++;

        ParseFunctionArguments(input);
        if (input->ChildCount() > 0)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(0, keyword, source));

        return input;
    }

    const FormatNode* Parser::ParseFormatCall()
    {
        const auto keyword = Current();
        const auto format = new FormatNode(Current());;
        index++;

        ParseFunctionArguments(format);
        return format;
    }

    const InvokeNode* Parser::ParseInvokeCall()
    {
        const auto keyword = Current();
        const auto invoke = new InvokeNode(Current());;
        index++;

        ParseFunctionArguments(invoke);
        if (invoke->ChildCount() < 1)
            ExceptionManager::Instance().AddChild(new MinimumFunctionArgumentException(1, keyword, source));

        return invoke;
    }

    const FuncRefNode* Parser::ParseFuncRefCall()
    {
        const auto keyword = Current();
        index++;

        const auto generic = ParseGeneric();
        index++;

        const auto funcRef = new FuncRefNode(generic, keyword);

        ParseFunctionArguments(funcRef);
        if (funcRef->ChildCount() != 2)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        return funcRef;
    }

    const ToStringNode* Parser::ParseToStringCall()
    {
        const auto keyword = Current();
        const auto toString = new ToStringNode(Current());;
        index++;

        ParseFunctionArguments(toString);
        if (toString->ChildCount() != 1)
            ExceptionManager::Instance().AddChild(new FunctionArgumentException(1, keyword, source));

        return toString;
    }
}