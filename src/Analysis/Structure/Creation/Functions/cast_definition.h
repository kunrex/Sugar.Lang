#ifndef CAST_DEFINITION_H
#define CAST_DEFINITION_H

#include "../../Core/Creation/function.h"

namespace Analysis::Structure::Creation
{
    class CastDefinition : public Core::Function
    {
        protected:
            CastDefinition(Enums::Describer describer, const Core::Interfaces::IDataType* creationType);
    };
}

#endif
