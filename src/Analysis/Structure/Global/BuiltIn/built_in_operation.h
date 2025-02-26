#ifndef BUILT_IN_OPERATION_H
#define BUILT_IN_OPERATION_H

#include "../../Core/built_in_function.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInOperation final : public Creation::OverloadDefinition, public Core::Interfaces::BuiltInFunction
    {
        public:
            BuiltInOperation(Tokens::Enums::SyntaxKind baseOperator, const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
