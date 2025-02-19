#include "constant_out_of_range_exception.h"

#include <format>

using namespace Tokens::Enums;

using namespace Analysis::Structure;

namespace Exceptions
{
    ConstantOutOfRangeException::ConstantOutOfRangeException(TypeKind type, const unsigned long index, const SourceFile* const source) : LogException(std::format("Constant does not lie in the range of {}", ToString(type)), index, source)
    { }
}
