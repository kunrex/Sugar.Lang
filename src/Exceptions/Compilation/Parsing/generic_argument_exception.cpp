#include "generic_argument_exception.h"

#include <format>

using namespace Tokens;

using namespace Analysis::Structure;

namespace Exceptions
{
    GenericArgumentException::GenericArgumentException(const int argumentCount, const Token& token, const SourceFile* const source) : ParsingException(std::format("{} type requires (a maximum of) {} generic argument", ToString(token.Kind()), argumentCount), token, source)
    { }
}
