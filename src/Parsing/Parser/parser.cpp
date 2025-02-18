#include "parser.h"

#include "../../Exceptions/exception_manager.h"
#include "../../Exceptions/Compiling/Parsing/token_expected_exception.h"

#include "../ParseNodes/invalid_node.h"

#include "../ParseNodes/Groups/source_file_node.h"

using namespace Exceptions;

using namespace Tokens;
using namespace Tokens::Enums;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

namespace Parsing
{
    const Token& Parser::Current() const { return index < source->TokenCount() ? source->TokenAt(index) : source->TokenAt(source->TokenCount()); }
    std::optional<std::reference_wrapper<Token>> Parser::LookAhead() const { return index >= source->TokenCount() - 1 ? std::nullopt : source->TokenAt(index + 1); }

    bool Parser::MatchType(const Token& token, const TokenType tokenType, const bool increment)
    {
        if (token.Type() == tokenType)
        {
            if (increment)
                index++;

            return  true;
        }

        return  false;
    }

    bool Parser::MatchToken(const Token& token, const SyntaxKind syntaxKind, const bool increment)
    {
        if (token.Kind() == syntaxKind)
        {
            if (increment)
                index++;

            return  true;
        }

        return  false;
    }

    bool Parser::MatchSeparator(const Token& token, const SeparatorKind separatorKind, const bool increment)
    {
        if (token.Type() != TokenType::Separator)
            return false;

        if (const auto converted = static_cast<SeparatorKind>(token.Kind()); (converted & separatorKind) == converted)
        {
            if (increment)
                index++;

            return  true;
        }

        return false;
    }

    bool Parser::MatchLookAhead(const TokenType tokenType, const bool increment)
    {
        const auto lookAhead = LookAhead();
        return lookAhead && MatchType(lookAhead->get(), tokenType, increment);
    }

    bool Parser::MatchLookAhead(const SyntaxKind syntaxKind, const bool increment)
    {
        const auto lookAhead = LookAhead();
        return lookAhead && MatchToken(lookAhead->get(), syntaxKind, increment);
    }

    bool Parser::MatchLookAhead(const SeparatorKind separatorKind, const bool increment)
    {
        const auto lookAhead = LookAhead();
        return lookAhead && MatchSeparator(lookAhead->get(), separatorKind, increment);
    }

    bool Parser::TryMatchType(const Token& token, const TokenType tokenType, const bool increment)
    {
        const bool result = MatchType(token, tokenType, increment);

        if (!result)
            ExceptionManager::Instance().AddChild(new TokenExpectedException(tokenType, token, source));

        return result;
    }

    bool Parser::TryMatchToken(const Token& token, const SyntaxKind syntaxKind, const bool increment)
    {
        const bool result = MatchToken(token, syntaxKind, increment);

        if (!result)
            ExceptionManager::Instance().AddChild(new TokenExpectedException(syntaxKind, token, source));

        return result;
    }

    bool Parser::TryMatchSeparator(const Token& token, const SeparatorKind kind, const bool increment)
    {
        const bool result = MatchSeparator(token, kind, increment);;

        if (!result)
            ExceptionManager::Instance().AddChild(new TokenExpectedException(kind, token, source));

        return result;
    }


    InvalidNode* Parser::ParseInvalid(const SeparatorKind breakOut)
    {
        const auto start = index;
        const SeparatorKind extra = SeparatorKind::Semicolon | SeparatorKind::FlowerOpenBracket | SeparatorKind::FlowerCloseBracket;
        const SeparatorKind match = breakOut | extra;

        for (; index < source->TokenCount(); index++)
        {
            if (const auto current = Current(); MatchSeparator(current, match))
            {
                if (MatchSeparator(current, extra) && !MatchSeparator(current, breakOut))
                    index--;

                break;
            }
        }

        return new InvalidNode(start);
    }

    void Parser::Parse(Analysis::Structure::SourceFile* const source)
    {
        this->source = source;

        const auto sourceNode = new SourceFileNode();
        for (index = 0; index < source->TokenCount(); index++)
            sourceNode->AddChild(ParseStatement());

        this->source->WithSourceNode(sourceNode);

        index = 0;
        this->source = nullptr;
    }
}
