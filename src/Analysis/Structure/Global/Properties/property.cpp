#include "property.h"

#include <format>

#include "../../../../Exceptions/Compilation/Analysis/Local/initialisation_exception.h"
#include "../../../Creation/Binding/binder_extensions.h"
#include "../../../Creation/Binding/constant_binder.h"
#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"
#include "../../Core/DataTypes/data_type.h"
#include "../../Core/Scoped/default_scoped.h"

using namespace std;

using namespace Services;

using namespace Exceptions;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    Property::Property(const string& name, const Enums::Describer describer, const IDataType* const creationType) : PropertyDefinition(name, describer, creationType, nullptr)
    { }

    Property::Property(const string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const value) : PropertyDefinition(name, describer, creationType, value)
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

    AutoImplementedProperty::AutoImplementedProperty(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IFunction* get, const IFunction* const set, const IParseNode* const value) : Property(name, describer, creationType, value), publicGet(get->CheckDescriber(Describer::Public)), publicSet(set->CheckDescriber(Describer::Public)), getInstruction("call " + get->FullName()), setInstruction("call " + set->FullName()), dependencyCount(0), resolvedDependencyCount(-1)
    { }

    bool AutoImplementedProperty::Readable() const { return true; }
    bool AutoImplementedProperty::Writable() const { return true; }

    bool AutoImplementedProperty::PublicGet() const { return publicGet; }
    bool AutoImplementedProperty::PublicSet() const { return publicSet; }

    const std::string& AutoImplementedProperty::SignatureGetString() const { return getInstruction; }
    const std::string& AutoImplementedProperty::SignatureSetString() const { return setInstruction; }

    void AutoImplementedProperty::BindLocal()
    {
        if (parseNode == nullptr || context != nullptr)
            return;

        resolvedDependencyCount++;
        if (resolvedDependencyCount < dependencyCount)
            return;

        context = ConstantCompile(this, parent);
        if (context != nullptr && context->CreationType() != creationType)
            PushException(new InitialisationException(context->CreationType(), creationType, parseNode->Token().Index(), parent->Parent()));
    }

    void AutoImplementedProperty::Transpile(StringBuilder& builder) const
    {
        builder.PushLine("");
        builder.PushLine(std::format(".field {} {} {} {}", AccessModifierString(this), string(AccessModifierString(this)) + (CheckDescriber(Describer::Static) ? "static" : ""), creationType->FullName(), name));
    }

    void AutoImplementedProperty::IncrementDependencyCount() { dependencyCount++; }

    GetProperty::GetProperty(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IFunction* const get) : Property(name, describer, creationType), publicGet(get->CheckDescriber(Describer::Public)), getInstruction("call " + get->FullName())
    { }

    bool GetProperty::Readable() const { return true; }
    bool GetProperty::Writable() const { return false; }

    bool GetProperty::PublicGet() const { return publicGet; }
    bool GetProperty::PublicSet() const { return false; }

    const std::string& GetProperty::SignatureGetString() const { return getInstruction; }
    const std::string& GetProperty::SignatureSetString() const { return getInstruction; }

    void GetProperty::BindLocal()
    { }

    void GetProperty::Transpile(StringBuilder& builder) const
    { }

    SetProperty::SetProperty(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IFunction* const set) : Property(name, describer, creationType), publicSet(set->CheckDescriber(Describer::Public)), setInstruction("call " + set->FullName())
    { }

    bool SetProperty::Readable() const { return false; }
    bool SetProperty::Writable() const { return true; }

    bool SetProperty::PublicGet() const { return false; }
    bool SetProperty::PublicSet() const { return publicSet; }

    const std::string& SetProperty::SignatureGetString() const { return setInstruction; }
    const std::string& SetProperty::SignatureSetString() const { return setInstruction; }

    void SetProperty::BindLocal()
    { }

    void SetProperty::Transpile(StringBuilder& builder) const
    { }

    GetSetProperty::GetSetProperty(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IFunction* const get, const IFunction* const set) : Property(name, describer, creationType), publicGet(get->CheckDescriber(Describer::Public)), publicSet(set->CheckDescriber(Describer::Public)), getInstruction("call " + get->FullName()), setInstruction("call " + set->FullName())
    { }

    bool GetSetProperty::Readable() const { return true; }
    bool GetSetProperty::Writable() const { return true; }

    bool GetSetProperty::PublicGet() const { return publicGet; }
    bool GetSetProperty::PublicSet() const { return publicSet; }

    const std::string& GetSetProperty::SignatureGetString() const { return getInstruction; }
    const std::string& GetSetProperty::SignatureSetString() const { return setInstruction; }

    void GetSetProperty::BindLocal()
    { }

    void GetSetProperty::Transpile(StringBuilder& builder) const
    { }
}
