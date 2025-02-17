#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#include "../created.h"
#include "../nameable.h"
#include "../describable.h"
#include "../Interfaces/i_read_write.h"

namespace Analysis::Structure::Core
{
    class Characteristic : public virtual Interfaces::INode, public Nameable, public Describable, public Created, public Interfaces::IReadWrite
    {
        protected:
            Characteristic(const std::string& name, Enums::Describer describer, const DataType* creationType);
    };
}

#endif
