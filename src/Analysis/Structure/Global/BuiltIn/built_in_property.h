#ifndef BUILT_IN_PROPERTY_H
#define BUILT_IN_PROPERTY_H

#include "../../Creation/Properties/property_definition.h"

namespace Analysis::Structure::Global
{
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
