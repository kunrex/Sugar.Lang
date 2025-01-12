#ifndef CONSTRUCTOR_DEFINITION_H
#define CONSTRUCTOR_DEFINITION_H

#include "../../../Core/Creation/function.h"

namespace Analysis::Structure::Creation
{
    class ConstructorDefinition : public Core::Function, public Core::FullyNameable
    {
        protected:
            ConstructorDefinition(Enums::Describer describer, const Core::DataType* creationType);
    };
}

#endif
