#include "global_variable.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    GlobalVariable::GlobalVariable(const std::string& name, const Enums::Describer describer, const DataType* creationType) : GlobalNode(), Variable(name, describer, creationType)
    { }

    void GlobalVariable::SetParent(const DataType* parent)
    {
        Child::SetParent(parent);
        fullName = parent->FullName() + "::" + name;
    }
}
