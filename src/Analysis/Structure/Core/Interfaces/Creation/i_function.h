#ifndef I_FUNCTION_H
#define I_FUNCTION_H

#include "../i_created.h"
#include "../i_describable.h"
#include "../i_fully_nameable.h"
#include "i_parametrized.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IFunction : public virtual IFullyNameable, public virtual IDescribable, public virtual ICreated, public virtual IParametrized
    {

    };
}

#endif
