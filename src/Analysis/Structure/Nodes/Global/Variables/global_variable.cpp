#include "global_variable.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    GlobalVariable::GlobalVariable(const std::string& name, const Enums::Describer describer, const DataType* creationType) : GlobalNode(), Variable(name, describer, creationType), DefaultValued(nullptr)
    { }

    GlobalVariable::GlobalVariable(const std::string& name, const Enums::Describer describer, const DataType* creationType, const ParseNodes::ParseNode* value) : GlobalNode(), Variable(name, describer, creationType), DefaultValued(value)
    { }

    MemberType GlobalVariable::MemberType() const { return MemberType::Field; }

    const std::string& GlobalVariable::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "::" + name;;

        return fullName;
    }
}
