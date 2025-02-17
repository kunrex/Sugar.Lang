#include "duplicate_structure_definition_exception.h"

#include <format>

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    DuplicateStructureDefinitionException::DuplicateStructureDefinitionException(const string& name, const unsigned long index, const SourceFile* source) : LogException(std::format("File: {} already defines a {}", source->Name(), name), index, source)
    { }
}
