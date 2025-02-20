#ifndef IMPLICIT_CAST_H
#define IMPLICIT_CAST_H

#include "../../Core/scoped.h"
#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Global
{
    class ImplicitCast final : public Core::Nameable, public Creation::CastDefinition, public Core::Scoped
    {
        public:
            ImplicitCast(Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::Groups::ScopeNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;

            [[nodiscard]] unsigned long ParameterCount() const override;
            const Core::DataType* ParameterAt(unsigned long index) const override;
    };
}

#endif
