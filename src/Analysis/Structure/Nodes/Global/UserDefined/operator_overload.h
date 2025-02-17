#ifndef OPERATOR_OVERLOAD_H
#define OPERATOR_OVERLOAD_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Global
{
    class OperatorOverload final : public Creation::OverloadDefinition, public Core::Scoped, public Core::FullyNameable
    {
        public:
            OperatorOverload(Tokens::Enums::SyntaxKind baseOperator, Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::Groups::ScopeNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
            [[nodiscard]] const std::string& SignatureString() const override;

            void AddArgument(const Creation::Variable* parameter) override;
    };
}

#endif
