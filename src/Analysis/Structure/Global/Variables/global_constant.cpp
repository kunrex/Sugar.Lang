#include "global_constant.h"

#include <format>

#include "../../Context/Constants/integer_constant.h"

#include "../../../Creation/Binding/constant_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    GlobalConstant::GlobalConstant(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* parseNode) : GlobalVariable(name, describer, creationType, parseNode), dependants()
    { }

    MemberType GlobalConstant::MemberType() const { return MemberType::ConstantField; }

    bool GlobalConstant::Readable() const { return true; }
    bool GlobalConstant::Writable() const { return false; }

    void GlobalConstant::BindLocal()
    {
        GlobalVariable::BindLocal();

        if (context != nullptr)
            for (const auto dependant: dependants)
                dependant->BindLocal();
    }

    void GlobalConstant::Transpile(Services::StringBuilder& builder) const
    {
        builder.PushLine(std::format(".field literal {} {} = {}", creationType->FullName(), name, ConstantString(this)));
    }

    void GlobalConstant::IncrementDependencyCount() { dependencyCount++; }

    void GlobalConstant::PushDependant(ICharacteristic* const characteristic) const
    {
        if(std::ranges::find(dependants, characteristic) == dependants.end())
        {
            dependants.push_back(characteristic);
            characteristic->IncrementDependencyCount();
        }
    }

    bool GlobalConstant::HasDependant(const ICharacteristic* characteristic) const
    {
        for (const auto dependant: dependants)
            if (dependant == characteristic || dependant->HasDependant(characteristic))
                return true;

        return false;
    }

    ImplicitEnumConstant::ImplicitEnumConstant(const std::string& name, const IDataType* const creationType, const ICharacteristic* const characteristic) : GlobalConstant(name, Describer::Public | Describer::Constexpr, creationType, nullptr), characteristic(characteristic)
    {
        if (characteristic == nullptr)
        {
            context = new IntegerConstant(0);
            return;
        }

        characteristic->PushDependant(this);

        dependencyCount = 1;
        resolvedDependencyCount = 0;
    }

    void ImplicitEnumConstant::BindLocal()
    {
        if (context != nullptr)
            return;

        resolvedDependencyCount++;
        if (resolvedDependencyCount < dependencyCount)
            return;

        const auto value = *reinterpret_cast<int*>(characteristic->Context()->Metadata());

        context = new IntegerConstant(value + 1);
        for (const auto dependant: dependants)
            dependant->BindLocal();
    }

    BuiltInConstant::BuiltInConstant(const std::string& name, const Enums::Describer describer, const IDataType* creationType, const IContextNode* const context) : Characteristic(name, describer, creationType, nullptr)
    {
        this->context = context;
    }

    MemberType BuiltInConstant::MemberType() const { return MemberType::ConstantField; }

    bool BuiltInConstant::Readable() const { return true; }
    bool BuiltInConstant::Writable() const { return false; }

    const std::string& BuiltInConstant::FullName() const { return fullName; }

    void BuiltInConstant::BindLocal()
    { }

    void BuiltInConstant::Transpile(Services::StringBuilder& builder) const
    { }

    void BuiltInConstant::IncrementDependencyCount()
    { }

    void BuiltInConstant::PushDependant(ICharacteristic* const characteristic) const
    { }

    bool BuiltInConstant::HasDependant(const ICharacteristic* characteristic) const { return false; }
}

