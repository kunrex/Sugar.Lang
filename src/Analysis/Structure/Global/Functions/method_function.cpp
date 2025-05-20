#include "method_function.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Creation::Binding;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    MethodFunction::MethodFunction(const string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : MethodDefinition(name, describer, creationType), Scoped(body)
    { }

    MemberType MethodFunction::MemberType() const { return MemberType::MethodDefinition; }

    const string& MethodFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} {} {} {}::{}{}",  CheckDescriber(Describer::Static) ? "" : "instance", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void MethodFunction::Bind()
    {
        BindScoped(this);
    }
}
