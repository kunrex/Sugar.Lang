#include "explicit_cast.h"

#include <format>

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    ExplicitCast::ExplicitCast(const Enums::Describer describer, const DataType* const creationType, const ScopeNode* const body) : CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType ExplicitCast::MemberType() const { return MemberType::ExplicitCast; }

    const string& ExplicitCast::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "::__explicit__" + creationType->Name();

        return fullName;
    }

    const string& ExplicitCast::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("{} {} {}{}", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", FullName(), ArgumentSignatureString());

        return signature;
    }

    const string& ExplicitCast::ArgumentSignatureString() const
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

    unsigned long ExplicitCast::ParameterCount() const { return argumentCount; }

    const DataType* ExplicitCast::ParameterAt(const unsigned long index) const { return VariableAt(index)->CreationType(); }
}
