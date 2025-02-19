#ifndef BUILT_IN_OPERATION_H
#define BUILT_IN_OPERATION_H

#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInOperation final : public Creation::OverloadDefinition
    {
        private:
            std::vector<const Core::DataType*> parameters;

        public:
            BuiltInOperation(Tokens::Enums::SyntaxKind baseOperator, const Core::DataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;;

            [[nodiscard]] const std::string& SignatureString() const override;
            [[nodiscard]] const std::string& ArgumentSignatureString() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
