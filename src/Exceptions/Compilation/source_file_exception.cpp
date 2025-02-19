#include "source_file_exception.h"

#include <format>

namespace Exceptions
{
    SourceFileException::SourceFileException(std::string path) : CompileException(std::format("Path at {}, is not found or is not a directory", path))
    { }
}
