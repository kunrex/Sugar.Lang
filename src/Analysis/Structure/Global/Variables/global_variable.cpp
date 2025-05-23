#include "global_variable.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../Core/Scoped/default_scoped.h"

using namespace std;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    GlobalVariable::GlobalVariable(const string& name, const Enums::Describer describer, const IDataType* const creationType) : Characteristic(name, describer, creationType, nullptr)
    { }

    GlobalVariable::GlobalVariable(const string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const parseNode) : Characteristic(name, describer, creationType, parseNode)
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
        auto scoped = DefaultScoped();
        context = BindExpression(parseNode, &scoped, scoped.Scope(), parent);
    }
}
