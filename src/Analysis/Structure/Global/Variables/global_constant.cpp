#include "global_constant.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    GlobalConstant::GlobalConstant(const string& name, const Enums::Describer describer, const IDataType* const creationType, const ParseNodes::ParseNode* parseNode) : GlobalVariable(name, describer, creationType, parseNode), dependencies(), value()
    { }

    bool GlobalConstant::Writable() const { return false; }

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

    void GlobalConstant::WithValue(long value) const
    {
        this->value = value;
    }

    void GlobalConstant::WithValue(double value) const
    {
        this->value = value;
    }

    void GlobalConstant::WithValue(const string& value) const
    {
        this->value = value;
    }

    template <typename TType>
    optional<TType> GlobalConstant::Value() const
    {
        if (const TType* v = std::get_if<TType>(&value)) {
            return *v;
        }

        return std::nullopt;
    }
}

