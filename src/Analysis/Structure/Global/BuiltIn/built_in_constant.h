#ifndef BUILT_IN_CONSTANT_H
#define BUILT_IN_CONSTANT_H

#include "../../Core/Creation/characteristic.h"

namespace Analysis::Structure::Global
{
    class BuiltInConstant final : public Core::Characteristic
    {
        public:
            BuiltInConstant(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const Core::Interfaces::IContextNode* context);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void IncrementDependencyCount() override;
            void PushDependant(ICharacteristic* characteristic) const override;
            [[nodiscard]] bool HasDependant(const ICharacteristic* characteristic) const override;
    };
}

#endif
