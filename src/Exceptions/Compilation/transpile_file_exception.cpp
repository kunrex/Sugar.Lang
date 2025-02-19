#include "transpile_file_exception.h"

namespace Exceptions
{
    TranspileFileException::TranspileFileException(const std::string& path) : CompileException("Failed writing to output file at: "+ path)
    { }
}
