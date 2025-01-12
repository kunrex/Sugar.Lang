#ifndef SET_H
#define SET_H

#include "accessor.h"

namespace Analysis::Structure::Creation
{
    class Set final : public Accessor
    {
        public:
            Set(Enums::Describer describer, const ParseNodes::ParseNode* body);
    };
}

#endif
