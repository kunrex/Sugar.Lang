#include "constructor.h"

#include <format>

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    Constructor::Constructor(const Enums::Describer describer, const DataType* const creationType, const ScopeNode* const body) : ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    MemberType Constructor::MemberType() const { return MemberType::Constructor; }

    const string& Constructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "::.ctor";

        return fullName;
    }

    const string& Constructor::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("void {}{}", FullName(), ArgumentSignatureString());

        return signature;
    }

    const string& Constructor::ArgumentSignatureString() const
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

    unsigned long Constructor::ParameterCount() const { return argumentCount; }

    const DataType* Constructor::ParameterAt(const unsigned long index) const { return VariableAt(index)->CreationType(); }
}

