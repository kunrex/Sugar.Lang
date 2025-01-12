#include "method_function.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    MethodFunction::MethodFunction(const string& name, const Enums::Describer describer, const DataType* creationType, const ParseNode* body) : MethodDefinition(name, describer, creationType), Scoped(body)
    { }

    void MethodFunction::SetParent(const DataType* parent)
    {
        GlobalNode::SetParent(parent);
        fullName = parent->FullName() + "::" + name;
    }

    bool MethodFunction::operator<(const MethodFunction& rhs) const
    {
        if (fullName != rhs.fullName)
            return fullName < rhs.fullName;

        return Function::operator<(rhs);
    }
}
