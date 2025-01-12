#include "generic_argument_exception.h"

#include <format>

using namespace Tokens;

using namespace Analysis::Structure;

namespace Exceptions
{
    GenericArgumentException::GenericArgumentException(int argumentCount, const Token& token, const SourceFile* source) : ParsingException(std::format("{} type requires {} generic argument", ToString(token.Kind()), argumentCount), token, source)
    { }
}
