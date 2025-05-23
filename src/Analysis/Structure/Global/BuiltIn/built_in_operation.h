#ifndef BUILT_IN_OPERATION_H
#define BUILT_IN_OPERATION_H

#include "../../Core/built_in_function.h"
#include "../../Core/Interfaces/Creation/i_built_in_overload.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInOperation final : public Creation::OverloadDefinition, public Core::BuiltInFunction, public virtual Core::Interfaces::IBuiltInOverload
    {
        private:
            const Core::Interfaces::OverloadFunction overloadDelegate;

        public:
            BuiltInOperation(Tokens::Enums::SyntaxKind baseOperator, const Core::Interfaces::IDataType* creationType, const std::string& instruction, Core::Interfaces::OverloadFunction overloadDelegate);

            [[nodiscard]] Enums::MemberType MemberType() const override;;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] Compilation::CompilationResult StaticCompile(const std::vector<Compilation::CompilationResult>& arguments) const override;

            void BindLocal() override;
    };
}

#endif
