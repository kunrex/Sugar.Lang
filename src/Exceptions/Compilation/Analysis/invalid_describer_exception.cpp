#include "invalid_describer_exception.h"

#include <format>

using namespace Analysis::Structure;
using namespace Analysis::Structure::Enums;

namespace Exceptions
{
    ExpectedDescriberException::ExpectedDescriberException(const Describer value, const unsigned long index, const SourceFile* const source) : LogException(std::format("Expected describer {}", ToString(value)), index, source)
    { }

    InvalidDescriberException::InvalidDescriberException(const Describer value, const Describer expected, const unsigned long index, const SourceFile* const source) : LogException(std::format("Allowed describers: {}, instead got: {}", ToString(expected), ToString(value)), index, source)
    { }
}
