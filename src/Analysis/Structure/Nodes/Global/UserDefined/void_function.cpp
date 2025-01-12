#include "void_function.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    VoidFunction::VoidFunction(const string& name, const Enums::Describer describer, const ParseNode* body) : VoidDefinition(name, describer), Scoped(body)
    { }

    void VoidFunction::SetParent(const DataType* parent)
    {
        GlobalNode::SetParent(parent);
        fullName = parent->FullName() + "::" + name;
    }

    bool VoidFunction::operator<(const VoidFunction& rhs) const
    {
        if (fullName != rhs.fullName)
            return fullName < rhs.fullName;

        return Function::operator<(rhs);
    }
}

