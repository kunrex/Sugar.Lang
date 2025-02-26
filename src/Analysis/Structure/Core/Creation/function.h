#ifndef FUNCTION_H
#define FUNCTION_H

#include "../created.h"
#include "../describable.h"
#include "../Interfaces/Creation/i_function.h"

#include "../../Global/global_node.h"

namespace Analysis::Structure::Core
{
    class Function : public Global::GlobalNode, public Describable, public Created, public virtual Interfaces::IFunction
    {
        protected:
            mutable std::string fullName;

            Function(Enums::Describer describer, const Interfaces::IDataType* creationType);
    };
}

#endif
