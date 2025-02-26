#ifndef BUILT_IN_CAST_H
#define BUILT_IN_CAST_H

#include "../../Core/built_in_function.h"
#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Global
{
    class BuiltInCast final : public Creation::CastDefinition, public Core::Interfaces::BuiltInFunction
    {
        public:
            BuiltInCast(const Core::Interfaces::IDataType* creationType, const std::string& instruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
