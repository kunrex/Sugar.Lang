#ifndef BUILT_IN_CONSTRUCTOR_H
#define BUILT_IN_CONSTRUCTOR_H

#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInConstructor final : public Creation::ConstructorDefinition
    {
        private:
            std::vector<const Core::DataType*> parameters;

        public:
            BuiltInConstructor(const Core::DataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
