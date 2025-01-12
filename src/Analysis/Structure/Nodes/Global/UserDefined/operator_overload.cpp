#include "operator_overload.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Tokens::Operators;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    OperatorOverload::OperatorOverload(const Operator* baseOperator, const Enums::Describer describer, const DataType* creationType, const ParseNode* body) : OverloadDefinition(baseOperator, describer, creationType), Scoped(body)
    { }

    void OperatorOverload::SetParent(const DataType* parent)
    {
        GlobalNode::SetParent(parent);
        fullName = parent->FullName() + "::__operator__" + std::to_string(static_cast<short>(baseOperator->Kind()));
    }

    bool OperatorOverload::operator<(const OperatorOverload& rhs) const
    {
        if (baseOperator->Kind() != rhs.baseOperator->Kind())
            return baseOperator->Kind() < rhs.baseOperator->Kind();

        return Function::operator<(rhs);
    }
}
