#ifndef BUILT_IN_CAST_H
#define BUILT_IN_CAST_H

#include "../../Creation/Functions/cast_definition.h"
#include "../../Core/Interfaces/i_built_in_parametrized.h"

namespace Analysis::Structure::Global
{
    class BuiltInCast final : public Creation::CastDefinition, public virtual Analysis::Core::Interfaces::IBuiltInParametrized
    {
        private:
            std::vector<const Core::DataType*> parameters;

        public:
            BuiltInCast(const Core::DataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;

            void PushParameterType(const Core::DataType* type) override;
    };
}

#endif
