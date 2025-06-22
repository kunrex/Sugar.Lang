#ifndef PROPERTY_H
#define PROPERTY_H

#include "../../Creation/Functions/void_definition.h"
#include "../../Creation/Functions/method_definition.h"
#include "../../Creation/Properties/property_definition.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class Property : public Creation::PropertyDefinition, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        public:
            Property(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
            Property(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* value);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void IncrementDependencyCount() override;

            void PushDependant(ICharacteristic* characteristic) const override;
            [[nodiscard]] bool HasDependant(const ICharacteristic* characteristic) const override;
    };

    class AutoImplementedProperty final : public Property
    {
        private:
            const bool publicGet;
            const bool publicSet;

            const std::string getInstruction;
            const std::string setInstruction;

            int dependencyCount;
            int resolvedDependencyCount;

        public:
            AutoImplementedProperty(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IFunction* get, const Core::Interfaces::IFunction* set, const ParseNodes::Core::Interfaces::IParseNode* value);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void IncrementDependencyCount() override;
    };

    class GetProperty final : public Property
    {
        private:
            const bool publicGet;
            const std::string getInstruction;

        public:
            GetProperty(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IFunction* get);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class SetProperty final : public Property
    {
        private:
            const bool publicSet;
            const std::string setInstruction;

        public:
            SetProperty(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IFunction* set);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class GetSetProperty final : public Property
    {
        private:
            const bool publicGet;
            const bool publicSet;

            const std::string getInstruction;
            const std::string setInstruction;

        public:
            GetSetProperty(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IFunction* get, const Core::Interfaces::IFunction* set);

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;
    };

    class BuiltInProperty final : public Creation::PropertyDefinition
    {
        protected:
            const bool readable;
            const bool writable;

            const std::string getInstruction;
            const std::string setInstruction;

        public:
            BuiltInProperty(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, bool readable, std::string getInstruction, bool writable, std::string setInstruction);

            [[nodiscard]]Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] bool PublicGet() const override;
            [[nodiscard]] bool PublicSet() const override;

            [[nodiscard]] const std::string& SignatureGetString() const override;
            [[nodiscard]] const std::string& SignatureSetString() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void IncrementDependencyCount() override;
            void PushDependant(ICharacteristic* characteristic) const override;
            [[nodiscard]] bool HasDependant(const ICharacteristic* characteristic) const override;
    };
}

#endif
