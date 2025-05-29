#ifndef CONSTRUCTOR_DEFINITION_H
#define CONSTRUCTOR_DEFINITION_H

#include "../../Core/Creation/function.h"
#include "../../Core/Interfaces/Creation/i_constructor.h"

namespace Analysis::Structure::Creation
{
    class ConstructorDefinition : public Core::Function, public virtual Core::Interfaces::IConstructor
    {
        protected:
            ConstructorDefinition(Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
    };
}

#endif
