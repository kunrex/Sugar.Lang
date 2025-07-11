#include "global_variable.h"

#include <format>

#include "../../../Creation/Binding/constant_binder.h"
#include "../../../Creation/Binding/binder_extensions.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

#include "../../../../Exceptions/exception_manager.h"
#include "../../../../Exceptions/Compilation/Analysis/Local/initialisation_exception.h"

using namespace Exceptions;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    GlobalVariable::GlobalVariable(const std::string& name, const Enums::Describer describer, const IDataType* const creationType) : Characteristic(name, describer, creationType, nullptr), dependencyCount(0), resolvedDependencyCount(-1)
    { }

    GlobalVariable::GlobalVariable(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const parseNode) : Characteristic(name, describer, creationType, parseNode), dependencyCount(0), resolvedDependencyCount(-1)
    { }

    MemberType GlobalVariable::MemberType() const { return MemberType::Field; }

    const std::string& GlobalVariable::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "::" + name;

        return fullName;
    }

    bool GlobalVariable::Readable() const { return true; }
    bool GlobalVariable::Writable() const { return true; }

    void GlobalVariable::BindLocal()
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
            ExceptionManager::PushException(InitialisationException(creationType, context->CreationType(), parseNode, parent));

        const auto constructor = CheckDescriber(Describer::Static) ? parent->StaticConstructor() : parent->InstanceConstructor();
        constructor->PushTranspilation(this);
    }

    void GlobalVariable::Transpile(Services::StringBuilder& builder) const
    {
        auto modifier = std::string(AccessModifierString(this));

        std::string_view result;
        if (CheckDescriber(Describer::Const))
            result = CheckDescriber(Describer::Static) ? "static initonly" : "initonly";
        else
            result = CheckDescriber(Describer::Static) ? "static" : "";

        if (!result.empty())
        {
            modifier.append(" ");
            modifier.append(result);
        }

        builder.PushLine(std::format(".field {} {} {} {}", AccessModifierString(this), modifier, creationType->FullName(), name));
    }

    void GlobalVariable::IncrementDependencyCount() {  dependencyCount++; }

    void GlobalVariable::PushDependant(ICharacteristic* const characteristic) const
    { }

    bool GlobalVariable::HasDependant(const ICharacteristic* characteristic) const { return false; }
}
