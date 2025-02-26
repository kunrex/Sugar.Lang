#ifndef I_PARAMETERIZED_H
#define I_PARAMETERIZED_H

#include "../i_created.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IParametrized
    {
        public:
            [[nodiscard]] virtual unsigned long ParameterCount() const = 0;
            [[nodiscard]] virtual const IDataType* ParameterAt(unsigned long index) const = 0;

            virtual ~IParametrized() = default;
    };
}

#endif
