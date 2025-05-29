#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "../../Core/Creation/characteristic.h"
#include "../../Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../../../../Services/child.h"

namespace Analysis::Structure::Global
{
    class GlobalVariable : public Core::Characteristic, public Services::ConstantChild<Core::Interfaces::IUserDefinedType>
    {
        protected:
            int dependencyCount;
            int resolvedDependencyCount;

        public:
            GlobalVariable(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
            GlobalVariable(const std::string& name, Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* parseNode);

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
