#ifndef BUILT_IN_VOID_H
#define BUILT_IN_VOID_H

#include "../../Creation/Functions/void_definition.h"
#include "../../Core/Interfaces/i_built_in_parametrized.h"

namespace Analysis::Structure::Global
{
    class BuiltInVoid final : public Creation::VoidDefinition, public virtual Analysis::Core::Interfaces::IBuiltInParametrized
    {
        private:
            std::vector<const Core::DataType*> parameters;

        public:
            BuiltInVoid(const std::string& name, Enums::Describer describer, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::DataType* ParameterAt(unsigned long index) const override;

            void PushParameterType(const Core::DataType* type) override;
    };
}

#endif
