#ifndef METHOD_FUNCTION_H
#define METHOD_FUNCTION_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/method_definition.h"
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

    class GeneratedGetFunction final : public Creation::MethodDefinition, public Core::DefaultScoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            const std::string name;

        public:
            GeneratedGetFunction(Enums::Describer describer, std::string name, const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };
}

#endif
