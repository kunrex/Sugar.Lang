#include "compile_exception.h"

namespace Exceptions
{
    CompileException::CompileException(std::string message) : message(std::move(message))
    { }

    const char* CompileException::what() const noexcept { return c_str; }
}

