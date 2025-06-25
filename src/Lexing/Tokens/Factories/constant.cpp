#include "constant.h"

using namespace Tokens::Enums;

namespace Tokens
{
    Constant::Constant() = default;

    Token Constant::Null(const unsigned long i) { return { i, TokenType::Constant, SyntaxKind::Null, static_cast<short>(TypeKind::Object), 0l }; }

    Token Constant::True(const unsigned long i) { return { i, TokenType::Constant, SyntaxKind::True, static_cast<short>(TypeKind::Boolean), static_cast<long>(true) }; }
    Token Constant::False(const unsigned long i) { return { i, TokenType::Constant, SyntaxKind::False, static_cast<short>(TypeKind::Boolean), static_cast<long>(false) }; }

    Token Constant::Character(const unsigned long i, const long value) { return { i, TokenType::Constant, SyntaxKind::Constant, static_cast<short>(TypeKind::Character), value }; }

    Token Constant::Short(const unsigned long i, const long value) { return { i, TokenType::Constant, SyntaxKind::Constant, static_cast<short>(TypeKind::Short), value }; }
    Token Constant::Int(const unsigned long i, const long value) { return { i, TokenType::Constant, SyntaxKind::Constant, static_cast<short>(TypeKind::Int), value }; }
    Token Constant::Long(const unsigned long i, const long value) { return { i, TokenType::Constant, SyntaxKind::Constant, static_cast<short>(TypeKind::Long), value }; }

    Token Constant::Float(const unsigned long i, const double value) { return { i, TokenType::Constant, SyntaxKind::Constant, static_cast<short>(TypeKind::Float), value }; }
    Token Constant::Double(const unsigned long i, const double value) { return { i, TokenType::Constant, SyntaxKind::Constant, static_cast<short>(TypeKind::Double), value }; }

    Token Constant::String(const unsigned long i, std::string value) { return { i, TokenType::Constant, SyntaxKind::Constant, static_cast<short>(TypeKind::String), std::move(value) }; }
}
