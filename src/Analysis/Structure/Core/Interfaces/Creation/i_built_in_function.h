#ifndef I_BUILT_IN_FUNCTION_H
#define I_BUILT_IN_FUNCTION_H

#include "i_function.h"
#include "i_built_in_parametrized.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IBuiltInFunction : public virtual IFunction, public virtual IBuiltInParametrized
    {

    };
}

#endif
