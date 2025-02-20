#ifndef FUNCTION_H
#define FUNCTION_H

#include "../created.h"
#include "../describable.h"
#include "../Interfaces/i_parametrized.h"

#include "../../Global/global_node.h"

namespace Analysis::Structure::Core
{
    class Function : public Global::GlobalNode, public IFullyNameable, public Describable, public Created, public virtual Interfaces::IParametrized
    {
        protected:
            mutable std::string fullName;

            Function(Enums::Describer describer, const DataType* creationType);
    };
}

#endif
