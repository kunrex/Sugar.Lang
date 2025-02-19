#include "compile_exception.h"

namespace Exceptions
{
    CompileException::CompileException(const std::string& message) : c_str(message.c_str())
    { }

    const char* CompileException::what() const noexcept { return c_str; }
}

