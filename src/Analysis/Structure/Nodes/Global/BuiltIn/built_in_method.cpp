#include "built_in_method.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInMethod::BuiltInMethod(const string& name, const Enums::Describer describer, const DataType* creationType) : MethodDefinition(name, describer, creationType)
    { }
}
