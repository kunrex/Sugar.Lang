#include "parser.h"

#include "../../Exceptions/exception_manager.h"
#include "../../Exceptions/Compilation/Parsing/invalid_token_exception.h"

#include "../../Lexing/Tokens/Enums/keyword_type.h"
#include "../ParseNodes/Describers/describer_keyword_node.h"

#include "../ParseNodes/Expressions/Unary/unary_node.h"
#include "../ParseNodes/Expressions/Binary/binary_node.h"

#include "../ParseNodes/Statements/empty_node.h"
#include "../ParseNodes/Statements/Control/break_node.h"
#include "../ParseNodes/Statements/Control/return_node.h"
#include "../ParseNodes/Statements/initialisation_node.h"
#include "../ParseNodes/Statements/throw_statement_node.h"
#include "../ParseNodes/Statements/Control/continue_node.h"
#include "../ParseNodes/Statements/expression_statement_node.h"
#include "../ParseNodes/Types/Keyword/anonymous_type_node.h"

using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Types;
using namespace ParseNodes::Values;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Expressions;
using namespace ParseNodes::Core::Interfaces;
using namespace ParseNodes::Functions::Calling;

namespace Parsing
{
    const IParseNode* Parser::ParseVariableDeclaration(const DescriberNode* const describer, const IParseNode* const type, const SeparatorKind breakSeparator)
    {
        const auto identifier = ParseIdentifier(true);

        const auto& current = Current();
        if (MatchToken(current, SyntaxKind::FlowerOpenBracket))
            return ParseProperty(describer, type, identifier);
        if (MatchSeparator(current, breakSeparator))
            return new DeclarationNode(describer, type, identifier, current);

        const auto declarations = new CompoundDeclarationNode(current);

        if (MatchToken(current, SyntaxKind::Assignment, true))
        {
            const auto initialise = new InitialisationNode(describer, type, identifier, ParseNonEmptyExpression(breakSeparator | SeparatorKind::Comma), Current());

            if (MatchSeparator(Current(), breakSeparator))
            {
                delete declarations;
                return initialise;
            }

            declarations->AddChild(initialise);
        }
        else
            declarations->AddChild(new DeclarationNode(describer, type, identifier, current));

        if (MatchToken(Current(), SyntaxKind::Comma, true))
        {
            std::cout << *Current().Value<std::string>() << std::endl;
            while (index < source->TokenCount())
            {
                const auto identify = ParseIdentifier(true);

                if (const auto& cur = Current(); MatchToken(cur, SyntaxKind::Comma, true))
                {
                    declarations->AddChild(new DeclarationNode(describer, type, identify, cur));
                    continue;
                }
                else if (MatchToken(cur, SyntaxKind::Assignment, true))
                {
                    declarations->AddChild(new InitialisationNode(describer, type, identifier, ParseNonEmptyExpression(breakSeparator | SeparatorKind::Comma), Current()));
                    if (MatchToken(Current(), SyntaxKind::Comma, true))
                        continue;;
                }

                if (MatchSeparator(Current(), breakSeparator))
                    return declarations;

                break;
            }
        }

        const auto invalid = ParseInvalid(breakSeparator);
        invalid->AddChild(declarations);

        TryMatchSeparator(Current(), breakSeparator);
        return invalid;
    }

    const DescriberNode* Parser::ParseDescriber()
    {
        TryMatchToken(Current(), SyntaxKind::BoxOpenBracket, true);

        const auto describer = new DescriberNode(source->TokenAt(index - 1));
        while (index < source->TokenCount())
        {
            const auto& current = Current();
            if (!MatchType(current, TokenType::Keyword))
            {
                Exceptions::ExceptionManager::Instance().AddChild(new Exceptions::InvalidTokenException(current, source));
                break;
            }

            if (const auto keywordType = static_cast<KeywordType>(current.Metadata()); keywordType != KeywordType::Describer)
            {
                Exceptions::ExceptionManager::Instance().AddChild(new Exceptions::InvalidTokenException(current, source));
                break;
            }

            describer->AddChild(new DescriberKeywordNode(current));

            if (MatchLookAhead(SeparatorKind::Comma, true))
                continue;
            if (MatchLookAhead(SeparatorKind::BoxCloseBracket, true))
            {
                index++;
                if (MatchToken(Current(), SyntaxKind::BoxOpenBracket, true))
                    continue;

                return describer;
            }

            break;
        }

        const auto invalid = ParseInvalid(SeparatorKind::BoxCloseBracket);
        delete invalid;

        TryMatchToken(Current(), SyntaxKind::BoxCloseBracket);
        return describer;
    }

    const IParseNode* Parser::ParseIdentifierStatement(const SeparatorKind breakSeparator)
    {
        if (MatchLookAhead(SyntaxKind::Colon))
        {
            const auto type =  ParseType();
            index += 2;

            return ParseVariableDeclaration(new DescriberNode(Current()), type, breakSeparator);
        }
        if (MatchLookAhead(TokenType::Identifier))
        {
            const auto type = ParseType();
            index += 2;

            return ParseFunction(new DescriberNode(Current()), type);
        }

        return new ExpressionStatementNode(ParseExpression(SeparatorKind::Semicolon), Current());
    }

    const IParseNode* Parser::ParseKeywordStatement(const SeparatorKind breakSeparator)
    {
        switch (const auto& current = Current(); current.Kind())
        {
            case SyntaxKind::Print:
                return ParsePrintCall();
            case SyntaxKind::Import:
                return ParseImportStatement();
            case SyntaxKind::Input:
            case SyntaxKind::Format:
            case SyntaxKind::Invoke:
            case SyntaxKind::Create:
            case SyntaxKind::ToString:
                return ParseExpression(breakSeparator);
            case SyntaxKind::Throw:
                {
                    index++;
                    return new ThrowStatementNode(ParseNonEmptyExpression(breakSeparator), current);
                }
            case SyntaxKind::If:
                return ParseIf();
            case SyntaxKind::While:
                return ParseWhile();
            case SyntaxKind::Do:
                return ParseDoWhile();
            case SyntaxKind::For:
                return ParseForLoop();
            case SyntaxKind::Break:
                {
                    const auto& keyword = Current();
                    index++;

                    TryMatchSeparator(Current(), SeparatorKind::Semicolon);
                    return new BreakNode(keyword);
                }
            case SyntaxKind::Return:
                {
                    index++;
                    if (MatchSeparator(Current(), breakSeparator))
                        return new ReturnNode(Current());

                    return new ReturnNode(ParseNonEmptyExpression(breakSeparator), Current());
                }
            case SyntaxKind::Continue:
                {
                    const auto keyword = Current();
                    index++;

                    TryMatchSeparator(Current(), SeparatorKind::Semicolon);
                    return new ContinueNode(keyword);
                }
            case SyntaxKind::Enum:
                return ParseEnumDefinition(new DescriberNode(Current()));
            case SyntaxKind::Class:
                return ParseClassDefinition(new DescriberNode(Current()));
            case SyntaxKind::Struct:
                return ParseStructDefinition(new DescriberNode(Current()));
            case SyntaxKind::Let:
                {
                    index++;
                    TryMatchToken(Current(), SyntaxKind::Colon, true);
                    return ParseVariableDeclaration(new DescriberNode(Current()), new AnonymousTypeNode(current), breakSeparator);
                }
            case SyntaxKind::Indexer:
                return ParseIndexer(new DescriberNode(Current()));
            case SyntaxKind::Constructor:
                return ParseConstructor(new DescriberNode(Current()));
            case SyntaxKind::Explicit:
                return ParseExplicitCast(new DescriberNode(Current()));
            case SyntaxKind::Implicit:
                return ParseImplicitCast(new DescriberNode(Current()));
            case SyntaxKind::Operator:
                return ParseOperatorOverload(new DescriberNode(Current()));
            default:
                {
                    if (const auto keywordType = static_cast<KeywordType>(current.Metadata()); keywordType == KeywordType::Type)
                    {
                        const auto type = ParseType();
                        index++;

                        const auto& cur = Current();
                        if (MatchToken(cur, SyntaxKind::Colon, true))
                            return ParseVariableDeclaration(new DescriberNode(Current()), type, breakSeparator);
                        if (MatchType(cur, TokenType::Identifier))
                            return ParseFunction(new DescriberNode(Current()), type);
                    }
                }
                break;
        }

        const auto invalid = ParseInvalid(breakSeparator);
        TryMatchSeparator(Current(), breakSeparator);
        return invalid;
    }

    const IParseNode* Parser::ParseDescriberStatement(const SeparatorKind breakSeparator)
    {
        const auto describer = ParseDescriber();

        switch (const auto& current = Current(); current.Type())
        {
            case TokenType::Identifier:
                {
                    if (MatchLookAhead(SyntaxKind::Colon))
                    {
                        const auto type = ParseType();
                        index += 2;

                        return ParseVariableDeclaration(describer, type, breakSeparator);
                    }

                    if (const auto entity = ParseEntity(breakSeparator); entity->NodeType() == NodeType::Identifier)
                    {
                        const auto type = CheckType(entity);
                        index++;

                        return ParseFunction(describer, type);
                    }
                    break;
                }
            case TokenType::Keyword:
                {
                    if (const auto keywordType = static_cast<KeywordType>(current.Metadata()); keywordType == KeywordType::Type)
                    {
                        const auto type = ParseType();
                        index++;

                        const auto& cur = Current();
                        if (MatchToken(cur, SyntaxKind::Colon, true))
                            return ParseVariableDeclaration(describer, type, breakSeparator);
                        if (MatchType(cur, TokenType::Identifier))
                            return ParseFunction(describer, type);
                    }
                    else
                    {
                        switch (current.Kind())
                        {
                            case SyntaxKind::Enum:
                                return ParseEnumDefinition(describer);
                            case SyntaxKind::Class:
                                return ParseClassDefinition(describer);
                            case SyntaxKind::Struct:
                                return ParseStructDefinition(describer);
                            case SyntaxKind::Indexer:
                                return ParseIndexer(describer);
                            case SyntaxKind::Constructor:
                                return ParseConstructor(describer);
                            case SyntaxKind::Explicit:
                                return ParseExplicitCast(describer);
                            case SyntaxKind::Implicit:
                                return ParseImplicitCast(describer);
                            case SyntaxKind::Operator:
                                return ParseOperatorOverload(describer);
                            case SyntaxKind::Let:
                                {
                                    index++;
                                    TryMatchToken(Current(), SyntaxKind::Colon, true);
                                    return ParseVariableDeclaration(describer, new AnonymousTypeNode(current), breakSeparator);
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
                break;
            default:
                break;
        }

        const auto invalid = ParseInvalid(breakSeparator);
        invalid->AddChild(describer);

        TryMatchSeparator(Current(), breakSeparator);
        return invalid;
    }

    const ScopeNode* Parser::ParseLazyScope()
    {
        if (MatchToken(Current(), SyntaxKind::FlowerOpenBracket))
            return ParseScope();

        const auto scope = new ScopeNode(Current());
        scope->AddChild(ParseStatement());

        return scope;
    }

    const ScopeNode* Parser::ParseScope()
    {
        TryMatchToken(Current(), SyntaxKind::FlowerOpenBracket, true);

        const auto scope = new ScopeNode(source->TokenAt(index - 1));
        for (; index < source->TokenCount(); index++)
        {
            if (MatchToken(Current(), SyntaxKind::FlowerCloseBracket))
                return scope;

            if (MatchToken(Current(), SyntaxKind::FlowerOpenBracket))
                scope->AddChild(ParseScope());

            scope->AddChild(ParseStatement());
        }

        TryMatchToken(Current(), SyntaxKind::FlowerCloseBracket);
        return scope;
    }

    const IParseNode* Parser::ParseStatement()
    {
        const auto& current = Current();
        if (MatchToken(current, SyntaxKind::BoxOpenBracket))
            return ParseDescriberStatement(SeparatorKind::Semicolon);
        if (MatchType(current, TokenType::Keyword))
            return ParseKeywordStatement(SeparatorKind::Semicolon);
        if (MatchType(current, TokenType::Identifier))
            return ParseIdentifierStatement(SeparatorKind::Semicolon);
        if (MatchToken(current, SyntaxKind::Semicolon))
            return new EmptyNode(current);

        const auto invalid = ParseInvalid(SeparatorKind::Semicolon);
        TryMatchToken(current, SyntaxKind::Semicolon);
        return invalid;
    }
}