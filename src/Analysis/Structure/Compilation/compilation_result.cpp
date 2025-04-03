#include "compilation_result.h"

using namespace std;

using namespace Tokens::Enums;

namespace Analysis::Structure::Compilation
{
    CompilationResult::CompilationResult(const TypeKind creationType, const long data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const TypeKind creationType, const double data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const TypeKind creationType, const string& data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const TypeKind creationType, const std::variant<long, double, string>& data) : creationType(creationType), data(data)
    { }
}
