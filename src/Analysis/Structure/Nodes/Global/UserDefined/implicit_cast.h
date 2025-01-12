#ifndef IMPLICIT_CAST_H
#define IMPLICIT_CAST_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Global
{
    class ImplicitCast final : public Creation::CastDefinition, Core::Scoped
    {
        public:
            ImplicitCast(Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* body);

            void SetParent(const Core::DataType* parent) override;

            bool operator<(const ImplicitCast& rhs) const;
    };
}

#endif
