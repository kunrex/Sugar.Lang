#ifndef I_BUILT_IN_PARAMETRIZED_H
#define I_BUILT_IN_PARAMETRIZED_H

#include "../../source_object.h"

namespace Analysis::Core::Interfaces
{
    class IBuiltInParametrized
    {
        public:
            virtual void PushParameterType(const Structure::Core::DataType* type) = 0;

            virtual ~IBuiltInParametrized() = default;
    };
}

#endif
