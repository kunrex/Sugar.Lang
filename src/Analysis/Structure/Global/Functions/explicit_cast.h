#ifndef EXPLICIT_CAST_H
#define EXPLICIT_CAST_H

#include "../../Core/Scoped/scoped.h"
#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Global
{
    class ExplicitCast final : public Core::Nameable, public Creation::CastDefinition, public Core::Scoped
    {
        public:
            ExplicitCast(Enums::Describer describer, const Core::Interfaces::IDataType* creationType, const ParseNodes::NodeCollection<ParseNodes::ParseNode>* body);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] const std::string& FullName() const override;
    };
}

#endif
