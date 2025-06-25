#include "property.h"

#include <format>

#include "../../../../Exceptions/exception_manager.h"
#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/constant_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

#include "../../../../Exceptions/Compilation/Analysis/Local/initialisation_exception.h"

using namespace Services;

using namespace Exceptions;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    Property::Property(const std::string& name, const Enums::Describer describer, const IDataType* const creationType) : PropertyDefinition(name, describer, creationType, nullptr)
    { }

    Property::Property(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const value) : PropertyDefinition(name, describer, creationType, value)
    { }

    MemberType Property::MemberType() const { return MemberType::Property; }

    const std::string& Property::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "::" + name;

        return fullName;
    }

    void Property::IncrementDependencyCount() { }

    void Property::PushDependant(ICharacteristic* const characteristic) const
    { }

    bool Property::HasDependant(const ICharacteristic* characteristic) const { return false; }

    AutoImplementedProperty::AutoImplementedProperty(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IFunction* get, const IFunction* const set, const IParseNode* const value) : Property(name, describer, creationType, value), get(get), set(set), dependencyCount(0), resolvedDependencyCount(-1)
    { }

    bool AutoImplementedProperty::Readable() const { return true; }
    bool AutoImplementedProperty::Writable() const { return true; }

    bool AutoImplementedProperty::PublicGet() const { return get->CheckDescriber(Describer::Public); }
    bool AutoImplementedProperty::PublicSet() const { return set->CheckDescriber(Describer::Public); }

    const std::string& AutoImplementedProperty::SignatureGetString() const { return get->FullName(); }
    const std::string& AutoImplementedProperty::SignatureSetString() const { return set->FullName(); }

    void AutoImplementedProperty::BindLocal()
    {
        if (parseNode == nullptr || context != nullptr)
            return;

        resolvedDependencyCount++;
        if (resolvedDependencyCount < dependencyCount)
            return;

        context = VariableCompile(this, parent);
        if (context == nullptr)
            return;

        if (context->CreationType() != creationType)
            ExceptionManager::PushException(InitialisationException(creationType, context->CreationType(), parseNode->Token().Index(), parent->Parent()));

        const auto constructor = CheckDescriber(Describer::Static) ? parent->StaticConstructor() : parent->InstanceConstructor();
        constructor->PushTranspilation(this);
    }

    void AutoImplementedProperty::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".field {} {} {} {}", AccessModifierString(this), std::string(AccessModifierString(this)) + (CheckDescriber(Describer::Static) ? "static" : ""), creationType->FullName(), name));
    }

    void AutoImplementedProperty::IncrementDependencyCount() { dependencyCount++; }

    GetProperty::GetProperty(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IFunction* const get) : Property(name, describer, creationType), get(get)
    { }

    bool GetProperty::Readable() const { return true; }
    bool GetProperty::Writable() const { return false; }

    bool GetProperty::PublicGet() const { return get->CheckDescriber(Describer::Public); }
    bool GetProperty::PublicSet() const { return false; }

    const std::string& GetProperty::SignatureGetString() const { return get->FullName(); }
    const std::string& GetProperty::SignatureSetString() const { return get->FullName(); }

    void GetProperty::BindLocal()
    { }

    void GetProperty::Transpile(StringBuilder& builder) const
    { }

    SetProperty::SetProperty(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IFunction* const set) : Property(name, describer, creationType), set(set)
    { }

    bool SetProperty::Readable() const { return false; }
    bool SetProperty::Writable() const { return true; }

    bool SetProperty::PublicGet() const { return false; }
    bool SetProperty::PublicSet() const { return set->CheckDescriber(Describer::Public); }

    const std::string& SetProperty::SignatureGetString() const { return set->FullName(); }
    const std::string& SetProperty::SignatureSetString() const { return set->FullName(); }

    void SetProperty::BindLocal()
    { }

    void SetProperty::Transpile(StringBuilder& builder) const
    { }

    GetSetProperty::GetSetProperty(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IFunction* const get, const IFunction* const set) : Property(name, describer, creationType), get(get), set(set)
    { }

    bool GetSetProperty::Readable() const { return true; }
    bool GetSetProperty::Writable() const { return true; }

    bool GetSetProperty::PublicGet() const { return get->CheckDescriber(Describer::Public); }
    bool GetSetProperty::PublicSet() const { return set->CheckDescriber(Describer::Public); }

    const std::string& GetSetProperty::SignatureGetString() const { return get->FullName(); }
    const std::string& GetSetProperty::SignatureSetString() const { return set->FullName(); }

    void GetSetProperty::BindLocal()
    { }

    void GetSetProperty::Transpile(StringBuilder& builder) const
    { }

    BuiltInProperty::BuiltInProperty(const std::string& name, const Enums::Describer describer, const IDataType* creationType, const bool readable, std::string getInstruction, const bool writable, std::string setInstruction) : PropertyDefinition(name, describer, creationType, nullptr), readable(readable), writable(writable), getInstruction(std::move(getInstruction)), setInstruction(std::move(setInstruction))
    { }

    MemberType BuiltInProperty::MemberType() const { return MemberType::BuiltInProperty; }

    const std::string& BuiltInProperty::FullName() const { return name; }

    bool BuiltInProperty::Readable() const { return readable; }
    bool BuiltInProperty::Writable() const { return writable; }

    bool BuiltInProperty::PublicGet() const { return readable; }
    bool BuiltInProperty::PublicSet() const { return writable; }

    const std::string& BuiltInProperty::SignatureGetString() const { return getInstruction; }
    const std::string& BuiltInProperty::SignatureSetString() const { return setInstruction; }

    void BuiltInProperty::BindLocal()
    { }

    void BuiltInProperty::Transpile(StringBuilder& builder) const
    { }

    void BuiltInProperty::IncrementDependencyCount()
    { }

    void BuiltInProperty::PushDependant(ICharacteristic* const characteristic) const
    { }

    bool BuiltInProperty::HasDependant(const ICharacteristic* characteristic) const { return false; }
}
