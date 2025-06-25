#include "compilation_result.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Compilation
{
    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const short data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const int data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const long data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const char data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const bool data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const float data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const double data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, std::string data) : creationType(creationType), data(std::move(data))
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, Primitive data) : creationType(creationType), data(std::move(data))
    { }
}
