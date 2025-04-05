#include "compilation_result.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Compilation
{
    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const long data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const double data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const string& data) : creationType(creationType), data(data)
    { }

    CompilationResult::CompilationResult(const IPrimitiveType* creationType, const std::variant<long, double, string>& data) : creationType(creationType), data(data)
    { }
}
