#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/constructor_definition.h"

namespace Analysis::Structure::Global
{
    class Constructor final : public Creation::ConstructorDefinition, Core::Scoped
    {
        public:
            Constructor(Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* body);

            void SetParent(const Core::DataType* parent) override;
    };
}

#endif
