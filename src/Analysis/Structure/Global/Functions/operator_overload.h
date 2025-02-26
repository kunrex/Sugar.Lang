#ifndef OPERATOR_OVERLOAD_H
#define OPERATOR_OVERLOAD_H

#include "../../Core/scoped.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Global
{
    class OperatorOverload final : public Core::Nameable, public Creation::OverloadDefinition, public Core::Scoped
    {
        public:
            OperatorOverload(Tokens::Enums::SyntaxKind baseOperator, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::NodeCollection<ParseNodes::ParseNode>* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
