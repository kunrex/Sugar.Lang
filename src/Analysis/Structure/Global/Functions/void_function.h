#ifndef VOID_FUNCTION_H
#define VOID_FUNCTION_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/void_definition.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class VoidFunction : public Creation::VoidDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        public:
            VoidFunction(const std::string& name, Enums::Describer describer, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class Entrypoint final : public VoidFunction
    {
        private:
            static Entrypoint* instance;

            Entrypoint(const std::string& name, Enums::Describer describer, const ParseNodes::Core::Interfaces::IParseNode* body);

        public:
            [[nodiscard]] static const Entrypoint* Instance();
            static Entrypoint* InitInstance(const std::string& name, Enums::Describer describer, const ParseNodes::Core::Interfaces::IParseNode* body);

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class GeneratedSetFunction final : public Creation::VoidDefinition, public Core::DefaultScoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            const std::string name;
            const Core::Interfaces::IDataType* creationType;

        public:
            GeneratedSetFunction(Enums::Describer describer, std::string name, const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };
}

#endif
