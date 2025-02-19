#include "method_function.h"

#include <format>

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    MethodFunction::MethodFunction(const string& name, const Enums::Describer describer, const DataType* const creationType, const ScopeNode* const body) : MethodDefinition(name, describer, creationType), Scoped(body)
    { }

    MemberType MethodFunction::MemberType() const { return MemberType::MethodDefinition; }

    const string& MethodFunction::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "::" + creationType->Name();

        return fullName;
    }

    const string& MethodFunction::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("{} {} {} {}{}", CheckDescriber(Describer::Static) ? "" : "instance", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", FullName(), ArgumentSignatureString());

        return signature;
    }

    const string& MethodFunction::ArgumentSignatureString() const
    {
        if (argumentSignature.empty())
        {
            argumentSignature += "(";
            for (int i = 0; i < argumentCount; i++)
            {
                argumentSignature += children.at(i)->FullName();
                if (i < argumentCount - 1)
                    argumentSignature += " ";
            }

            argumentSignature += ")";
        }

        return argumentSignature;
    }

    unsigned long MethodFunction::ParameterCount() const { return argumentCount; }

    const DataType* MethodFunction::ParameterAt(const unsigned long index) const { return VariableAt(index)->CreationType(); }
}
