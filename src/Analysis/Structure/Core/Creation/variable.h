#ifndef VARIABLE_H
#define VARIABLE_H

#include "../created.h"
#include "../nameable.h"
#include "../describable.h"
#include "../Interfaces/i_node.h"
#include "../Interfaces/i_read_write.h"

namespace Analysis::Structure::Core
{
    class Variable : public virtual Interfaces::INode, public Nameable, public Describable, public Created, public Interfaces::IReadWrite
    {
        protected:
            Variable(const std::string& name, Enums::Describer describer, const DataType* creationType);
    };
}

#endif
