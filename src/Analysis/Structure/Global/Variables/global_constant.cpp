#include "global_constant.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    GlobalConstant::GlobalConstant(const string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* parseNode) : GlobalVariable(name, describer, creationType, parseNode), dependencies()
    { }

    MemberType GlobalConstant::MemberType() const { return MemberType::ConstantField; }

    const std::string& GlobalConstant::FullName() const { return fullName; }

    bool GlobalConstant::Readable() const { return true; }
    bool GlobalConstant::Writable() const { return false; }

    bool GlobalConstant::Compiled() const { return context != nullptr; }

    void GlobalConstant::PushDependency(const IConstant* const constant) const
    {
        dependencies.push_back(constant);
    }

    bool GlobalConstant::IsDependent(const IConstant* const constant) const
    {
        for (const auto dependency : dependencies)
            if (dependency == constant || dependency->IsDependent(constant))
                return true;

        return false;
    }
}

