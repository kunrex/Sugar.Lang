#include "void_function.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    VoidFunction::VoidFunction(const string& name, const Enums::Describer describer, const ScopeNode* body) : VoidDefinition(name, describer), Scoped(body)
    { }

    void VoidFunction::AddArgument(const LocalVariable* parameter)
    {
        Scoped::AddArgument(parameter);
        PushParameterType(parameter->CreationType());
    }
}

