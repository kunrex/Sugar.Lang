#ifndef GLOBAL_CONSTANT_H
#define GLOBAL_CONSTANT_H

#include <vector>

#include "global_variable.h"

namespace Analysis::Structure::Global
{
    class GlobalConstant : public GlobalVariable
    {
        protected:
            mutable std::vector<ICharacteristic*> dependants;

        public:
            GlobalConstant(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* parseNode);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void IncrementDependencyCount() override;
            void PushDependant(ICharacteristic* characteristic) const override;
            [[nodiscard]] bool HasDependant(const ICharacteristic* characteristic) const override;
    };

    class ImplicitEnumConstant final : public GlobalConstant
    {
        private:
            const ICharacteristic* characteristic;

        public:
            ImplicitEnumConstant(const std::string& name, const Core::Interfaces::IDataType* creationType, const ICharacteristic* characteristic);

            void BindLocal() override;
    };
}

#endif
