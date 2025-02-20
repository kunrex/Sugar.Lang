#ifndef VARIABLE_H
#define VARIABLE_H

#include "../created.h"
#include "../nameable.h"
#include "../describable.h"

namespace Analysis::Structure::Core
{
    class Variable : public Nameable, public Describable, public Created
    {
        protected:
            Variable(const std::string& name, Enums::Describer describer, const DataType* creationType);
    };
}

#endif
