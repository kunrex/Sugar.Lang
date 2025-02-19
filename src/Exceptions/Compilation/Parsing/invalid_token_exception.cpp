#include "invalid_token_exception.h"

#include <format>

using namespace Tokens;

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidTokenException::InvalidTokenException(const Token& token, const SourceFile* const source) : ParsingException(std::format("invalid token: {} detected", ToString(token.Kind())), token, source)
    {

    }

}
