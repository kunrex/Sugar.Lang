#ifndef BUILT_IN_CONSTRUCTOR_H
#define BUILT_IN_CONSTRUCTOR_H

#include "../../Core/built_in_function.h"
#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInConstructor final : public Creation::ConstructorDefinition, public Core::BuiltInFunction
    {
        public:
            BuiltInConstructor(const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            void BindLocal() override;

            void Transpile(Services::StringBuilder& builder) const override;

            void PushTranspilation(Services::StringBuilder& builder) const override;
            void PushTranspilation(const Core::Interfaces::ICharacteristic* characteristic) override;
    };
}

#endif
