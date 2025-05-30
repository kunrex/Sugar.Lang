#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/constructor_definition.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"
#include "../../Core/Interfaces/Creation/i_constructor.h"

#include "../../../../Services/child.h"
#include "../../Core/Scoped/default_scoped.h"

namespace Analysis::Structure::Global
{
    class Constructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        public:
            Constructor(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };

    class ImplicitConstructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Core::DefaultScoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            std::vector<const Core::Interfaces::ICharacteristic*> characteristics;

        public:
            ImplicitConstructor(Enums::Describer describer, const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };

    class StaticImplicitConstructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Core::DefaultScoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            std::vector<const Core::Interfaces::ICharacteristic*> characteristics;

        public:
            explicit StaticImplicitConstructor(const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };

    class DefinedConstructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            std::vector<const Core::Interfaces::ICharacteristic*> characteristics;

        public:
            DefinedConstructor(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };

    class StaticDefinedConstructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Core::Scoped, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            std::vector<const Core::Interfaces::ICharacteristic*> characteristics;

        public:
            StaticDefinedConstructor(const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };
}

#endif
