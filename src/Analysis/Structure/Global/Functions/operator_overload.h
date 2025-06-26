#ifndef OPERATOR_OVERLOAD_H
#define OPERATOR_OVERLOAD_H

#include "../../Core/Interfaces/Creation/i_built_in_overload.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

namespace Analysis::Structure::Global
{
    class BaseOverload : public virtual Core::Interfaces::IOperatorOverload
    {
        protected:
            const Tokens::Enums::SyntaxKind baseOperator;

            explicit BaseOverload(Tokens::Enums::SyntaxKind baseOperator);

        public:
            [[nodiscard]] Tokens::Enums::SyntaxKind Operator() const override;
    };

    class OperatorOverload final : public BaseOverload
    {
        private:
            const IFunction* definition;

        public:
            OperatorOverload(Tokens::Enums::SyntaxKind baseOperator, const IFunction* definition);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] Enums::Describer Describer() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* CreationType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool ValidateDescriber(Enums::Describer allowed) const override;

            [[nodiscard]] bool MatchDescriber(Enums::Describer expected) const override;
            [[nodiscard]] bool CheckDescriber(Enums::Describer describer) const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;
    };

    class GeneratedOverload : public Core::Function, public BaseOverload, public Core::BuiltInFunction
    {
        public:
            GeneratedOverload(Tokens::Enums::SyntaxKind baseOperator, const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;
    };

    class BuiltInOverload final : public GeneratedOverload, public virtual Core::Interfaces::IBuiltInOverload
    {
        private:
            const Core::Interfaces::OverloadFunction overloadDelegate;

        public:
            BuiltInOverload(Tokens::Enums::SyntaxKind baseOperator, const Core::Interfaces::IDataType* creationType, const std::string& instruction, Core::Interfaces::OverloadFunction overloadDelegate);

            [[nodiscard]] Compilation::CompilationResult StaticCompile(const std::vector<Compilation::CompilationResult>& arguments) const override;
    };
}

#endif
