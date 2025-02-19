#include "log_exception.h"

#include <format>

using namespace Analysis::Structure;

namespace Exceptions
{
    LogException::LogException(const std::string& message, const unsigned long index, const SourceFile* const source) : CompileException(std::format("Exception: {}.\n\tAt index: {}, file: {}", message, index, source->FullName()))
    { }
}
