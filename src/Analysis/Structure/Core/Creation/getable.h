#ifndef GETABLE_H
#define GETABLE_H

#include "../Interfaces/i_read_write.h"
#include "../../Nodes/Creation/Properties/Accessors/get.h"

namespace Analysis::Structure::Core
{
    class Getable : public Interfaces::IReadWrite
    {
        protected:
            Creation::Get* const get;

            explicit Getable(Creation::Get* get);

        public:
            [[nodiscard]] const Creation::Get* Get() const;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            ~Getable() override;
    };
}

#endif
