#ifndef BUILT_IN_METHOD_H
#define BUILT_IN_METHOD_H

#include "../../Creation/Functions/method_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInMethod final : public Creation::MethodDefinition
    {
        private:
            std::vector<const Core::DataType*> parameters;

        public:
            BuiltInMethod(const std::string& name, Enums::Describer describer, const Core::DataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
