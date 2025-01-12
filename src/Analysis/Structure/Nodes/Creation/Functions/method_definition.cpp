#include "method_definition.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    MethodDefinition::MethodDefinition(const string& name, const Enums::Describer describer, const DataType* creationType) : FunctionDefinition(name, describer, creationType)
    { }

    bool MethodDefinition::Readable() const { return true; }
}
