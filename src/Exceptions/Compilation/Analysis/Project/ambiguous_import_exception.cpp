#include "ambiguous_import_exception.h"

#include <format>

using namespace Analysis::Structure;

namespace Exceptions
{
    AmbiguousImportException::AmbiguousImportException(const std::string& type1, const std::string& type2, const unsigned long index, const SourceFile* const source) : LogException(std::format("Ambiguous reference between: `{}` and `{}`", type1, type2), index, source)
    { }
}
