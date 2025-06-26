#include "duplicate_structure_definition_exception.h"

#include <format>

using namespace Analysis::Structure;

namespace Exceptions
{
    DuplicateStructureDefinitionException::DuplicateStructureDefinitionException(const unsigned long index, const SourceFile* const source) : LogException(std::format("File: {} already defines a structure with the same name", source->Name()), index, source)
    { }
}
