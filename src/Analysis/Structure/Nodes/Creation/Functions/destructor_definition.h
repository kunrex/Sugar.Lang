#ifndef DESTRUCTOR_DEFINITION_H
#define DESTRUCTOR_DEFINITION_H

#include "../../../Core/Creation/function.h"

namespace Analysis::Structure::Creation
{
    class DestructorDefinition : public Core::Function, public Core::FullyNameable
    {
        protected:
            DestructorDefinition(Enums::Describer describer, const Core::DataType* creationType);
    };
}

#endif
