#include "ambiguous_import_exception.h"

#include <format>

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    AmbiguousImportException::AmbiguousImportException(const string& type1, const string& type2, const unsigned long index, const SourceFile* source) : LogException(std::format("Ambiguous reference between: '{}' and '{}'", type1, type2), index, source)
    { }
}
