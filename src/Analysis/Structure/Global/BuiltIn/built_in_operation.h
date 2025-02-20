#ifndef BUILT_IN_OPERATION_H
#define BUILT_IN_OPERATION_H

#include "../../Creation/Functions/overload_definition.h"
#include "../../Core/Interfaces/i_built_in_parametrized.h"

namespace Analysis::Structure::Global
{
    class BuiltInOperation final : public Creation::OverloadDefinition, public virtual Analysis::Core::Interfaces::IBuiltInParametrized
    {
        private:
            std::vector<const Core::DataType*> parameters;

        public:
            BuiltInOperation(Tokens::Enums::SyntaxKind baseOperator, const Core::DataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;

            void PushParameterType(const Core::DataType* type) override;
    };
}

#endif
