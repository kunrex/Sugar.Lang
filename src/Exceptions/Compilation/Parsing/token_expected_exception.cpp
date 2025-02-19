#include "token_expected_exception.h"

#include <format>

using namespace Tokens;
using namespace Tokens::Enums;

using namespace Analysis::Structure;

namespace Exceptions
{
    TokenExpectedException::TokenExpectedException(const TokenType expected, const Token& token, const SourceFile* const source) : ParsingException(std::format("Token: {} expected", ToString(expected)), token, source)
    { }

    TokenExpectedException::TokenExpectedException(const SyntaxKind expected, const Token& token, const SourceFile* const source) : ParsingException(std::format("Token: {} expected", ToString(expected)), token, source)
    { }

    TokenExpectedException::TokenExpectedException(const SeparatorKind expected, const Token& token, const SourceFile* const source) : ParsingException(std::format("Token: {} expected", ToString(expected)), token, source)
    { }
}
