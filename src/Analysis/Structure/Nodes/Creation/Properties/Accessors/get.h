#ifndef GET_H
#define GET_H

#include "accessor.h"

namespace Analysis::Structure::Creation
{
    class Get final : public Accessor
    {
        public:
            Get(Enums::Describer describer, const ParseNodes::ParseNode* body);
    };
}

#endif
