#ifndef OPERATOR_OVERLOAD_H
#define OPERATOR_OVERLOAD_H

#include "../../Creation/Functions/overload_definition.h"

#include "../../Core/Scoped/scoped.h"
#include "../../Core/Interfaces/Creation/i_built_in_overload.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class OperatorOverload final : public Core::Nameable, public Creation::OverloadDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        public:
            OperatorOverload(Tokens::Enums::SyntaxKind baseOperator, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class ImplicitOverload : public Creation::OverloadDefinition, public Core::BuiltInFunction
    {
        public:
            ImplicitOverload(Tokens::Enums::SyntaxKind baseOperator, const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class BuiltInOverload final : public ImplicitOverload, public virtual Core::Interfaces::IBuiltInOverload
    {
        private:
            const Core::Interfaces::OverloadFunction overloadDelegate;

        public:
            BuiltInOverload(Tokens::Enums::SyntaxKind baseOperator, const Core::Interfaces::IDataType* creationType, const std::string& instruction, Core::Interfaces::OverloadFunction overloadDelegate);

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] Compilation::CompilationResult StaticCompile(const std::vector<Compilation::CompilationResult>& arguments) const override;
    };
}

#endif
