#include "invalid_import_path_exception.h"

#include <format>

using namespace std;

using namespace Tokens;

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidImportPathException::InvalidImportPathException(const string& path, const unsigned long index, const SourceFile* const source) : LogException(std::format("Path at `{}` was not found. Import statements use a local path", path), index, source)
    { }
}
