#include "separator.h"

using namespace Tokens::Enums;

namespace Tokens
{
    Separator::Separator() = default;

    Token Separator::Create(const unsigned long i, const SyntaxKind syntaxKind, const std::string& value)
    {
        return { i, TokenType::Separator, syntaxKind, value };
    }

    Token Separator::Dot(const unsigned long i) { return Create(i, SyntaxKind::Dot, "."); }
    Token Separator::Comma(const unsigned long i) { return Create(i, SyntaxKind::Comma, ","); }

    Token Separator::Colon(const unsigned long i) { return Create(i, SyntaxKind::Colon, ":"); }
    Token Separator::Semicolon(const unsigned long i) { return Create(i, SyntaxKind::Semicolon, ";"); }

    Token Separator::QuestionMark(const unsigned long i) { return Create(i, SyntaxKind::QuestionMark, "?"); }

    Token Separator::OpenBracket(const unsigned long i) { return Create(i, SyntaxKind::OpenBracket, "("); }
    Token Separator::CloseBracket(const unsigned long i) { return Create(i, SyntaxKind::CloseBracket, ")"); }

    Token Separator::BoxOpenBracket(const unsigned long i) { return Create(i, SyntaxKind::BoxOpenBracket, "["); }
    Token Separator::BoxCloseBracket(const unsigned long i) { return Create(i, SyntaxKind::BoxCloseBracket, "]"); }

    Token Separator::FlowerOpenBracket(const unsigned long i) { return Create(i, SyntaxKind::FlowerOpenBracket, "{"); }
    Token Separator::FlowerCloseBracket(const unsigned long i) { return Create(i, SyntaxKind::FlowerCloseBracket, "}"); }
}