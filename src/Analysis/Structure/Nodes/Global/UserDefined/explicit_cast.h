#ifndef EXPLICIT_CAST_H
#define EXPLICIT_CAST_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Global
{
    class ExplicitCast final : public Creation::CastDefinition, Core::Scoped
    {
        public:
            ExplicitCast(Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* body);

            void SetParent(const Core::DataType* parent) override;

            bool operator<(const ExplicitCast& rhs) const;
    };
}

#endif
