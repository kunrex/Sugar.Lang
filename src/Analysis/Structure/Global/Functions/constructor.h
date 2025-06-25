#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "../../Creation/Functions/constructor_definition.h"

#include "../../Core/Scoped/scoped.h"
#include "../../Core/built_in_function.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

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

            void PushTranspilation(Services::StringBuilder& builder, int& slotSize) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };

    class ImplicitConstructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            std::vector<const Core::Interfaces::ICharacteristic*> characteristics;

        public:
            ImplicitConstructor(Enums::Describer describer, const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder, int& slotSize) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };

    class StaticImplicitConstructor final : public Core::Nameable, public Creation::ConstructorDefinition, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        private:
            std::vector<const Core::Interfaces::ICharacteristic*> characteristics;

        public:
            explicit StaticImplicitConstructor(const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder, int& slotSize) const override;
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

            void PushTranspilation(Services::StringBuilder& builder, int& slotSize) const override;
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

            void PushTranspilation(Services::StringBuilder& builder, int& slotSize) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };

    class BuiltInConstructor final : public Creation::ConstructorDefinition, public Core::BuiltInFunction
    {
        public:
            BuiltInConstructor(const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder, int& slotSize) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };
}

#endif
