#ifndef I_BUILT_IN_PARAMETRIZED_H
#define I_BUILT_IN_PARAMETRIZED_H

#include "i_parametrized.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IBuiltInParametrized : public virtual IParametrized
    {
        public:
            virtual void PushParameterType(const IDataType* type) = 0;
    };
}

#endif
