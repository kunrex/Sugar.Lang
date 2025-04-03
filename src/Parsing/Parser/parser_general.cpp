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

using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;
using namespace ParseNodes::Statements;
using namespace ParseNodes::Expressions;
using namespace ParseNodes::Functions::Calling;

namespace Parsing
{
    const ParseNode* Parser::ParseVariableDeclaration(const DescriberNode* const describer, const ParseNode* const type, const SeparatorKind breakSeparator)
    {
        const auto identifier = ParseIdentifier(true);

        const auto current = Current();
        if (MatchToken(current, SyntaxKind::FlowerOpenBracket))
            return ParseProperty(describer, type, identifier);
        if (MatchSeparator(current, breakSeparator))
            return new DeclarationNode(describer, type, identifier, current);;

        const auto declarations = new CompoundDeclarationNode(current);
        if (MatchToken(current, SyntaxKind::Equals, true))
        {
            const auto initialise = new InitialisationNode(describer, type, identifier, ParseNonEmptyExpression(breakSeparator | SeparatorKind::Comma), Current());
            if (MatchSeparator(Current(), breakSeparator))
            {
                delete declarations;
                return initialise;
            }
        }

        if (MatchToken(Current(), SyntaxKind::Comma, true))
        {
            while (index < source->TokenCount())
            {
                const auto identify = ParseIdentifier(true);

                if (const auto cur = Current(); MatchToken(cur, SyntaxKind::Comma, true))
                {
                    declarations->AddChild(new DeclarationNode(describer, type, identify, cur));
                    continue;
                }
                else if (MatchToken(cur, SyntaxKind::Equals, true))
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
            const auto current = Current();
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
                if (TryMatchToken(Current(), SyntaxKind::BoxOpenBracket, true))
                    continue;

                index--;
                return describer;
            }

            break;
        }

        const auto invalid = ParseInvalid(SeparatorKind::BoxCloseBracket);
        delete invalid;

        TryMatchToken(Current(), SyntaxKind::BoxCloseBracket);
        return describer;
    }

    const ParseNode* Parser::ParseIdentifierStatement(const SeparatorKind breakSeparator)
    {
        if (MatchLookAhead(SyntaxKind::Colon))
        {
            const auto type =  ParseType();
            index += 2;

            return ParseVariableDeclaration(new DescriberNode(Current()), type, breakSeparator);
        }

        const auto entity = ParseEntity(breakSeparator);

        if (const auto lookAhead = LookAhead(); lookAhead)
        {
            switch (lookAhead->get().Type())
            {
                case TokenType::UnaryOperator:
                    {
                        const auto unary = new UnaryNode(*lookAhead, entity);
                        index += 2;

                        if (const auto cur = Current(); MatchType(cur, TokenType::BinaryOperator | TokenType::AssignmentOperator))
                        {
                            const auto expression = ParseNonEmptyExpression(SeparatorKind::Semicolon);
                            const auto binary = new BinaryNode(cur, unary, expression);

                            TryMatchToken(Current(), SyntaxKind::Semicolon);
                            return new ExpressionStatementNode(binary, Current());
                        }
                        else if (MatchSeparator(cur, SeparatorKind::Semicolon))
                            return new ExpressionStatementNode(unary, cur);

                        break;
                    }
                case TokenType::BinaryOperator:
                case TokenType::AssignmentOperator:
                    {
                        index += 2;

                        const auto expression = ParseNonEmptyExpression(breakSeparator);
                        const auto binary = new BinaryNode(*lookAhead, entity, expression);

                        TryMatchSeparator(Current(), breakSeparator);
                        return new ExpressionStatementNode(binary, Current());
                    }
                case TokenType::Identifier:
                    {
                        const auto type = CheckType(entity);
                        index++;

                        return ParseFunction(new DescriberNode(Current()), type);
                    }
                case TokenType::Separator:
                    {
                        if (TryMatchSeparator(*lookAhead, breakSeparator))
                            return entity;
                    }
                    break;
                default:
                    break;
            }
        }

        const auto invalid = ParseInvalid(breakSeparator);
        TryMatchSeparator(Current(), breakSeparator);
        return invalid;
    }

    const ParseNode* Parser::ParseKeywordStatement(const SeparatorKind breakSeparator)
    {
        switch (const auto current = Current(); current.Kind())
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
                    const auto keyword = Current();
                    index++;

                    TryMatchSeparator(Current(), SeparatorKind::Semicolon);
                    return new BreakNode(keyword);
                }
            case SyntaxKind::Return:
                {
                    if (MatchLookAhead(breakSeparator))
                    {
                        index++;
                        return new ReturnNode(Current());
                    }

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
            default:
                {
                    if (const auto keywordType = static_cast<KeywordType>(current.Metadata()); keywordType == KeywordType::Type)
                    {
                        const auto type = ParseType();
                        index++;

                        const auto cur = Current();
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

    const ParseNode* Parser::ParseDescriberStatement(const SeparatorKind breakSeparator)
    {
        const auto describer = ParseDescriber();
        index++;

        switch (const auto current = Current(); current.Type())
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

                        const auto cur = Current();
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
                            case SyntaxKind::Explicit:
                                return ParseExplicitCast(describer);
                            case SyntaxKind::Implicit:
                                return ParseImplicitCast(describer);
                            case SyntaxKind::Operator:
                                return ParseOperatorOverload(describer);
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

            scope->AddChild(ParseLazyScope());
        }

        TryMatchToken(Current(), SyntaxKind::FlowerCloseBracket);
        return scope;
    }

    const ParseNode* Parser::ParseStatement()
    {
        const auto current = Current();
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