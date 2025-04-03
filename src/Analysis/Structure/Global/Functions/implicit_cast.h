#ifndef IMPLICIT_CAST_H
#define IMPLICIT_CAST_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/cast_definition.h"


namespace Analysis::Structure::Global
{
    class ImplicitCast final : public Core::Nameable, public Creation::CastDefinition, public Core::Scoped
    {
        public:
            ImplicitCast(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::Core::Interfaces::IParseNode* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
