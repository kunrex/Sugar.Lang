#ifndef I_FUNCTION_H
#define I_FUNCTION_H

#include "i_parametrized.h"

#include "../i_node.h"
#include "../i_created.h"
#include "../i_describable.h"
#include "../i_fully_nameable.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IFunction : public virtual INode, public virtual IDescribable, public virtual IFullyNameable, public virtual ICreated, public virtual IParametrized
    {

    };
}

#endif
