#ifndef OPERATOR_OVERLOAD_H
#define OPERATOR_OVERLOAD_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Global
{
    class OperatorOverload final : public Creation::OverloadDefinition, public Core::Scoped
    {
        public:
            OperatorOverload(const Tokens::Operators::Operator* baseOperator, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* body);

            void SetParent(const Core::DataType* parent) override;

            bool operator<(const OperatorOverload& rhs) const;
    };
}

#endif
