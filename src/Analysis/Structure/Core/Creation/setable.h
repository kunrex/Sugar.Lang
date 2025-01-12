#ifndef SETABLE_H
#define SETABLE_H

#include "../Interfaces/i_read_write.h"
#include "../../Nodes/Creation/Properties/Accessors/set.h"

namespace Analysis::Structure::Core
{
    class Setable : public Interfaces::IReadWrite
    {
        protected:
            Creation::Set* const set;

            explicit Setable(Creation::Set* set);

        public:
            [[nodiscard]] const Creation::Set* Set() const;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            ~Setable() override;
    };
}

#endif
