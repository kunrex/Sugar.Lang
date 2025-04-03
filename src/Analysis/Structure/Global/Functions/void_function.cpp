#include "void_function.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    VoidFunction::VoidFunction(const string& name, const Enums::Describer describer, const IParseNode* const body) : VoidDefinition(name, describer), Scoped(body)
    { }

    MemberType VoidFunction::MemberType() const { return MemberType::MethodDefinition; }

    const string& VoidFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} void {} {}::{}{}",  CheckDescriber(Describer::Static) ? "" : "instance", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }
}

