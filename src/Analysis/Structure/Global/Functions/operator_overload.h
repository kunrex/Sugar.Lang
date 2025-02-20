#ifndef OPERATOR_OVERLOAD_H
#define OPERATOR_OVERLOAD_H

#include "../../Core/scoped.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Global
{
    class OperatorOverload final : public Core::Nameable, public Creation::OverloadDefinition, public Core::Scoped
    {
        public:
            OperatorOverload(Tokens::Enums::SyntaxKind baseOperator, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::Groups::ScopeNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
