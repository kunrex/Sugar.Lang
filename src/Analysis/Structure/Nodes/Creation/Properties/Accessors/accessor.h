#ifndef ACCESSOR_H
#define ACCESSOR_H

#include "../../../../Core/scoped.h"
#include "../../../../Core/describable.h"

namespace Analysis::Structure::Creation
{
    class Accessor : public Core::Describable, public Core::Scoped
    {
        protected:
            Accessor(Enums::Describer describer, const ParseNodes::ParseNode* body);
    };
}

#endif
