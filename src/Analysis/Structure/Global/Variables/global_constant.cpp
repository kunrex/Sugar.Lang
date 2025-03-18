#include "global_constant.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    GlobalConstant::GlobalConstant(const string& name, const Enums::Describer describer, const IDataType* const creationType, const ParseNodes::ParseNode* parseNode) : GlobalVariable(name, describer, creationType, parseNode), compiled(false), dependencies()
    { }

    MemberType GlobalConstant::MemberType() const { return MemberType::ConstantField; }

    const std::string& GlobalConstant::FullName() const { return fullName; }

    bool GlobalConstant::Readable() const { return compiled; }

    bool GlobalConstant::Writable() const { return false; }

    void GlobalConstant::Compile(const std::string& value)
    {
        if (!compiled)
        {
            fullName = value;
            compiled = true;
        }
    }

    void GlobalConstant::PushDependency(const ICharacteristic* const constant)
    {
        dependencies.push_back(constant);
    }

    bool GlobalConstant::IsDependent(const ICharacteristic* const constant) const
    {
        for (const auto dependency : dependencies)
            if (dependency == constant)
                return true;

        return false;
    }
}

