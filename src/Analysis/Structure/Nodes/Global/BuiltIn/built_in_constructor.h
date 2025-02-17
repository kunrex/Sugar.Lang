#ifndef BUILT_IN_CONSTRUCTOR_H
#define BUILT_IN_CONSTRUCTOR_H

#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInConstructor final : public Creation::ConstructorDefinition
    {
        public:
            BuiltInConstructor(const Core::DataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] const std::string& SignatureString() const override;
    };
}

#endif
