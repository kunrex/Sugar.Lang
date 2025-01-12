#ifndef GET_SET_H
#define GET_SET_H

#include "getable.h"
#include "setable.h"

namespace Analysis::Structure::Core
{
    class GetSet : public Getable, Setable
    {
        protected:
            GetSet(Creation::Get* get, Creation::Set* set);

        public:
            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
