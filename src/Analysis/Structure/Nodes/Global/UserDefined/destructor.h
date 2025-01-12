#ifndef DESTRUCTOR_H
#define DESTRUCTOR_H

#include "../../../Core/scoped.h"
#include "../../Creation/Functions/destructor_definition.h"

namespace Analysis::Structure::Global
{
    class Destructor final : public Creation::DestructorDefinition, Core::Scoped
    {
        public:
            Destructor(Enums::Describer describer, const Core::DataType* creationType, const ParseNodes::ParseNode* body);

            void SetParent(const Core::DataType* parent) override;
    };
}

#endif //DESTRUCTOR_H
