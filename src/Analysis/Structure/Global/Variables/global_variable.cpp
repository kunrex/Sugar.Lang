#include "global_variable.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    GlobalVariable::GlobalVariable(const string& name, const Enums::Describer describer, const DataType* creationType) : Characteristic(name, describer, creationType, nullptr)
    { }

    GlobalVariable::GlobalVariable(const string& name, const Enums::Describer describer, const DataType* creationType, const ParseNodes::ParseNode* value) : Characteristic(name, describer, creationType, value)
    { }

    MemberType GlobalVariable::MemberType() const { return MemberType::Field; }

    const string& GlobalVariable::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "::" + name;

        return fullName;
    }

    bool GlobalVariable::Readable() const { return true; }
    bool GlobalVariable::Writable() const { return true; }
}
