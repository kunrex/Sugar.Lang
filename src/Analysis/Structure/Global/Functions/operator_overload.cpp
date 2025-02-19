#include "operator_overload.h"

#include <format>

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    OperatorOverload::OperatorOverload(const SyntaxKind baseOperator, const Enums::Describer describer, const DataType* const creationType, const Groups::ScopeNode* const body) : OverloadDefinition(baseOperator, describer, creationType), Scoped(body)
    { }

    MemberType OperatorOverload::MemberType() const { return MemberType::OperatorOverload; }

    const string& OperatorOverload::FullName() const
    {
        if (fullName.empty())
            fullName = std::format("{}::__operator__{}", parent->FullName(), static_cast<short>(baseOperator));

        return fullName;
    }

    const string& OperatorOverload::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("{} {} {}{}", CreationType()->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", FullName(), ArgumentSignatureString());

        return signature;
    }

    const string& OperatorOverload::ArgumentSignatureString() const
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

    unsigned long OperatorOverload::ParameterCount() const { return argumentCount; }

    const DataType* OperatorOverload::ParameterAt(const unsigned long index) const { return VariableAt(index)->CreationType(); }
}
