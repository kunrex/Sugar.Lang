#ifndef I_BUILT_IN_FUNCTION_H
#define I_BUILT_IN_FUNCTION_H

#include "../DataTypes/i_data_type.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IBuiltInFunction
    {
        public:
            virtual void PushParameterType(const IDataType* type) = 0;

            virtual ~IBuiltInFunction() = default;
    };
}

#endif
