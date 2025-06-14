#include "parser.h"
#include "../../Analysis/Structure/Wrappers/Reference/exception.h"

#include "../../Exceptions/exception_manager.h"
#include "../../Exceptions/Compilation/Parsing/invalid_token_exception.h"
#include "../../Exceptions/Compilation/Parsing/token_expected_exception.h"

#include "../../Lexing/Tokens/Enums/keyword_type.h"

#include "../ParseNodes/Describers/describer_keyword_node.h"

#include "../ParseNodes/Types/Keyword/anonymous_type_node.h"

#include "../ParseNodes/Statements/empty_node.h"
#include "../ParseNodes/Statements/Control/break_node.h"
#include "../ParseNodes/Statements/Control/return_node.h"
#include "../ParseNodes/Statements/initialisation_node.h"
#include "../ParseNodes/Statements/throw_statement_node.h"
#include "../ParseNodes/Statements/Control/continue_node.h"
#include "../ParseNodes/Statements/expression_statement_node.h"
#include "../ParseNodes/Types/Keyword/void_type_node.h"

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
    void Parser::ParseCompoundDeclaration(CompoundDeclarationNode* const declarations, const SeparatorKind breakSeparator)
    {
        while (index < source->TokenCount())
        {
            if (!MatchType(Current(), TokenType::Identifier))
            {
                Exceptions::ExceptionManager::Instance().AddChild(new Exceptions::InvalidTokenException(Current(), source));
                break;
            }

            declarations->AddChild(ParseIdentifier(true));

            if (const auto& current = Current(); MatchToken(current, SyntaxKind::Assignment, true))
                declarations->AddChild(ParseNonEmptyExpression(breakSeparator | SeparatorKind::Comma));
            else
                declarations->AddChild(new EmptyNode(current));

            const auto& current = Current();
            if (MatchSeparator(current, breakSeparator))
                return;

            TryMatchSeparator(current, SeparatorKind::Comma, true);
        }
    }

    const IParseNode* Parser::ParseVariableDeclaration(const DescriberNode* const describer, const IParseNode* const type, const SeparatorKind breakSeparator)
    {
        const auto identifier = ParseIdentifier(true);

        const auto& current = Current();

        if (MatchToken(current, SyntaxKind::FlowerOpenBracket))
            return ParseProperty(describer, type, identifier);
        if (MatchSeparator(current, breakSeparator))
            return new DeclarationNode(describer, type, identifier, current);
        if (MatchToken(current, SyntaxKind::Comma, true))
        {
            const auto compound = new CompoundDeclarationNode(current, describer, type);
            compound->AddChild(identifier);

            ParseCompoundDeclaration(compound, breakSeparator);
            return compound;
        }
        if (MatchToken(current, SyntaxKind::Assignment, true))
        {
            const auto value = ParseNonEmptyExpression(breakSeparator | SeparatorKind::Comma);
            if (MatchSeparator(Current(), breakSeparator))
                return new InitialisationNode(describer, type, identifier, value, current);

            if (MatchToken(Current(), SyntaxKind::Comma, true))
            {
                const auto compound = new CompoundDeclarationNode(current, describer, type);
                compound->AddChild(identifier);
                compound->AddChild(value);

                ParseCompoundDeclaration(compound, breakSeparator);
                return compound;
            }
        }

        Exceptions::ExceptionManager::Instance().AddChild(new Exceptions::InvalidTokenException(current, source));

        const auto invalid =  ParseInvalid(breakSeparator);
        TryMatchSeparator(Current(), breakSeparator);

        return invalid;
    }

    const DescriberNode* Parser::ParseDescriber()
    {
        const auto& start = Current();
        TryMatchToken(start, SyntaxKind::BoxOpenBracket, true);

        const auto describer = new DescriberNode(start);

        while (index < source->TokenCount())
        {
            if (const auto& current = Current(); !MatchType(current, TokenType::Keyword) || static_cast<KeywordType>(current.Metadata()) != KeywordType::Describer)
            {
                Exceptions::ExceptionManager::Instance().AddChild(new Exceptions::InvalidTokenException(current, source));
                break;
            }
            else
            {
                describer->AddChild(new DescriberKeywordNode(current));
                index++;
            }

            if (MatchToken(Current(), SyntaxKind::BoxCloseBracket))
            {
                if (MatchLookAhead(SyntaxKind::BoxOpenBracket, true))
                {
                    index++;
                    continue;
                }

                break;
            }

            TryMatchToken(Current(), SyntaxKind::Comma, true);
        }

        TryMatchToken(Current(), SyntaxKind::BoxCloseBracket, true);
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
                return new ExpressionStatementNode(ParseExpression(breakSeparator), current);
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
                    const auto& keyword = current;
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
                    const auto keyword = current;
                    index++;

                    TryMatchSeparator(Current(), SeparatorKind::Semicolon);
                    return new ContinueNode(keyword);
                }
            case SyntaxKind::Get:
                return ParseGet(new DescriberNode(current));
            case SyntaxKind::Set:
                return ParseSet(new DescriberNode(current));
            case SyntaxKind::Enum:
                return ParseEnumDefinition(new DescriberNode(current));
            case SyntaxKind::Class:
                return ParseClassDefinition(new DescriberNode(current));
            case SyntaxKind::Struct:
                return ParseStructDefinition(new DescriberNode(current));
            case SyntaxKind::Let:
                {
                    index++;
                    TryMatchToken(Current(), SyntaxKind::Colon, true);
                    return ParseVariableDeclaration(new DescriberNode(Current()), new AnonymousTypeNode(current), breakSeparator);
                }
            case SyntaxKind::Void:
                {
                    const auto describer = new DescriberNode(current);
                    const auto type = new VoidTypeNode(current);
                    index++;

                    return ParseFunction(describer, type);
                }
            case SyntaxKind::Indexer:
                return ParseIndexer(new DescriberNode(current));
            case SyntaxKind::Constructor:
                return ParseConstructor(new DescriberNode(current));
            case SyntaxKind::Explicit:
                return ParseExplicitCast(new DescriberNode(current));
            case SyntaxKind::Implicit:
                return ParseImplicitCast(new DescriberNode(current));
            case SyntaxKind::Operator:
                return ParseOperatorOverload(new DescriberNode(current));
            default:
                {
                    switch (static_cast<KeywordType>(current.Metadata()))
                    {
                        case KeywordType::Describer:
                            return ParseDescriberStatement(breakSeparator);
                        case KeywordType::Type:
                            {
                                if (MatchLookAhead(SyntaxKind::Colon))
                                {
                                    const auto type = ParseType();
                                    index += 2;

                                    return ParseVariableDeclaration(new DescriberNode(Current()), type, breakSeparator);
                                }
                                if (MatchLookAhead(TokenType::Identifier))
                                {
                                    const auto type = ParseType();
                                    index++;

                                    return ParseFunction(new DescriberNode(Current()), type);
                                }

                                return new ExpressionStatementNode(ParseExpression(SeparatorKind::Semicolon), Current());
                            }
                        default:
                            break;
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
                    switch (current.Kind())
                    {
                        case SyntaxKind::Get:
                            return ParseGet(describer);
                        case SyntaxKind::Set:
                            return ParseSet(describer);
                        case SyntaxKind::Enum:
                            return ParseEnumDefinition(describer);
                        case SyntaxKind::Class:
                            return ParseClassDefinition(describer);
                        case SyntaxKind::Struct:
                            return ParseStructDefinition(describer);
                        case SyntaxKind::Void:
                            {
                                const auto type = new VoidTypeNode(current);
                                index++;

                                return ParseFunction(describer, type);
                            }
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
                        default:
                            break;
                    }

                    if (const auto keywordType = static_cast<KeywordType>(current.Metadata()); keywordType == KeywordType::Type)
                    {
                        const auto type = ParseType();
                        index++;

                        const auto& cur = Current();
                        if (MatchToken(cur, SyntaxKind::Colon, true))
                            return ParseVariableDeclaration(describer, type, breakSeparator);
                        if (MatchType(cur, TokenType::Identifier))
                            return ParseFunction(describer, type);

                        const auto invalid = ParseInvalid(breakSeparator);
                        TryMatchSeparator(Current(), breakSeparator);
                        invalid->AddChild(type);
                        return invalid;
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
            {
                scope->AddChild(ParseScope());
                continue;
            }

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