#ifndef CONSTRUCTOR_DEFINITION_H
#define CONSTRUCTOR_DEFINITION_H

#include "../../Core/Creation/function.h"

namespace Analysis::Structure::Creation
{
    class ConstructorDefinition : public Core::Function
    {
        protected:
            ConstructorDefinition(Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
    };
}

#endif
