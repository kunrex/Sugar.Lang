#include "global_variable.h"

#include <format>

#include "../../../../Exceptions/Compilation/Analysis/Local/initialisation_exception.h"
#include "../../../Creation/Binding/binder_extensions.h"
#include "../../../Creation/Binding/constant_binder.h"
#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"
#include "../../Core/Scoped/default_scoped.h"

using namespace std;

using namespace Exceptions;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    GlobalVariable::GlobalVariable(const string& name, const Enums::Describer describer, const IDataType* const creationType) : Characteristic(name, describer, creationType, nullptr), dependencyCount(0), resolvedDependencyCount(-1)
    { }

    GlobalVariable::GlobalVariable(const string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const parseNode) : Characteristic(name, describer, creationType, parseNode), dependencyCount(0), resolvedDependencyCount(-1)
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
            PushException(new InitialisationException(context->CreationType(), creationType, parseNode->Token().Index(), parent->Parent()));

        context->Print("", true);
    }

    void GlobalVariable::Transpile(Services::StringBuilder& builder) const
    {
        builder.PushLine("");
        auto modifier = string(AccessModifierString(this));

        std::string_view result;
        if (CheckDescriber(Describer::Const))
            result = CheckDescriber(Describer::Static) ? "static initonly" : "initonly";
        else
            result = CheckDescriber(Describer::Static) ? "static" : "";

        if (!result.empty())
        {
            modifier += " ";
            modifier += result;
        }

        builder.PushLine(std::format(".field {} {} {} {}", AccessModifierString(this), modifier, creationType->FullName(), name));
    }

    void GlobalVariable::IncrementDependencyCount() {  dependencyCount++; }

    void GlobalVariable::PushDependant(ICharacteristic* const characteristic) const
    { }

    bool GlobalVariable::HasDependant(const ICharacteristic* characteristic) const { return false; }
}
