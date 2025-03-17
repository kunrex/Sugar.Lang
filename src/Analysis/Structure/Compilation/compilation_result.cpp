#include "compilation_result.h"

namespace Analysis::Structure::Compilation
{
    CompilationResult::CompilationResult(const TypeCode creationType, const long data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const TypeCode creationType, const double data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const TypeCode creationType, const std::string& data) : creationType(creationType), data(data)
    { }
}
