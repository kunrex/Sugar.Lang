#ifndef BUILT_IN_FUNCTION_H
#define BUILT_IN_FUNCTION_H

#include <vector>

#include "Interfaces/Creation/i_function.h"
#include "Interfaces/Creation/i_built_in_function.h"

namespace Analysis::Structure::Core::Interfaces
{
    class BuiltInFunction : public virtual IFunction, public virtual IBuiltInFunction
    {
        private:
            std::vector<const IDataType*> parameters;

        public:
            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const IDataType* ParameterAt(unsigned long index) const override;

            void PushParameterType(const IDataType* type) override;
    };
}

#endif
