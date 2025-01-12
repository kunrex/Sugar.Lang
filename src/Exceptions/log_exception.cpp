#include "log_exception.h"

#include <format>

using namespace Analysis::Structure;

namespace Exceptions
{
    LogException::LogException(const std::string& message, const unsigned long index, const SourceFile* source) : CompileException(message), index(index), sourcePath(source->FullName())
    { }

    const char* LogException::what() const noexcept
    {
        return std::format("Exception: {}. At index: {}, file: {}", message, index, sourcePath).c_str();
    }
}
