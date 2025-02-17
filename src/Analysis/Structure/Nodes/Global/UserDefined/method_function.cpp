#include "method_function.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    MethodFunction::MethodFunction(const string& name, const Enums::Describer describer, const DataType* creationType, const ScopeNode* body) : MethodDefinition(name, describer, creationType), Scoped(body)
    { }

    void MethodFunction::AddArgument(const Creation::Variable* parameter)
    {
        Scoped::AddArgument(parameter);
        PushParameterType(parameter->CreationType());
    }
}
