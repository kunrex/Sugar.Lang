#include "initialisation_exception.h"

#include <format>

using namespace Analysis::Structure;
using namespace Analysis::Structure::Core::Interfaces;

namespace Exceptions
{
    InitialisationException::InitialisationException(const IDataType* const expected, const IDataType* const actual, unsigned long index, const SourceFile* const source) : LogException(std::format("Value initialised to type of: {}. Expected: {}", actual->FullName(), expected->FullName()), index, source)
    { }
}
