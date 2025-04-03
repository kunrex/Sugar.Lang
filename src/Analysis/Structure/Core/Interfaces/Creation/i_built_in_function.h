#ifndef I_BUILT_IN_FUNCTION_H
#define I_BUILT_IN_FUNCTION_H

#include "i_built_in_function.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IBuiltInFunction : public virtual IFunction
    {
        public:
            virtual void PushParameterType(const IDataType* type) = 0;
    };
}

#endif
