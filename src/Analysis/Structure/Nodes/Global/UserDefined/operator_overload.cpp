#include "operator_overload.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    OperatorOverload::OperatorOverload(const SyntaxKind baseOperator, const Enums::Describer describer, const DataType* creationType, const Groups::ScopeNode* body) : OverloadDefinition(baseOperator, describer, creationType), Scoped(body)
    { }

    MemberType OperatorOverload::MemberType() const { return MemberType::OperatorOverload; }

    const std::string& OperatorOverload::FullName() const
    {
        if (fullName.empty())
            fullName = std::format("{}::__operator__{}", parent->FullName(), static_cast<short>(baseOperator));

        return fullName;
    }

    const std::string& OperatorOverload::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("{} {}{}", CreationType()->FullName(), FullName(), ArgumentSignatureString());

        return signature;
    }

    void OperatorOverload::AddArgument(const Creation::Variable* parameter)
    {
        Scoped::AddArgument(parameter);
        PushParameterType(parameter->CreationType());
    }
}
