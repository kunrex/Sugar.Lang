#ifndef PROPERTY_H
#define PROPERTY_H

#include "../../Core/Creation/characteristic.h"
#include "../../Core/Interfaces/Creation/i_property_signature.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class PropertyDefinition : public Core::Characteristic, public virtual Core::Interfaces::IPropertySignature
    {
        protected:
            PropertyDefinition(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* parseNode);
    };

    class Property : public PropertyDefinition, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
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
            const Core::Interfaces::IFunction* get;
            const Core::Interfaces::IFunction* set;

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
            const Core::Interfaces::IFunction* get;

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
            const Core::Interfaces::IFunction* set;

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
            const Core::Interfaces::IFunction* get;
            const Core::Interfaces::IFunction* set;

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

    class BuiltInProperty final : public PropertyDefinition
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
