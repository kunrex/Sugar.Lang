#ifndef BUILT_IN_CAST_H
#define BUILT_IN_CAST_H

#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInCast final : public Creation::CastDefinition
    {
        public:
            BuiltInCast(const Core::DataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            [[nodiscard]] const std::string& SignatureString() const override;
    };
}

#endif
