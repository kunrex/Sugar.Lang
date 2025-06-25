#ifndef METHOD_FUNCTION_H
#define METHOD_FUNCTION_H

#include "../../Creation/Functions/method_definition.h"

#include "../../Core/Scoped/scoped.h"
#include "../../Core/built_in_function.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class MethodFunction final : public Creation::MethodDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        public:
            MethodFunction(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class GeneratedGetFunction final : public Creation::MethodDefinition, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            const std::string variableName;

        public:
            GeneratedGetFunction(Enums::Describer describer, std::string variableName, const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class BuiltInMethod final : public Creation::MethodDefinition, public Core::BuiltInFunction
    {
        public:
            BuiltInMethod(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };
}

#endif
