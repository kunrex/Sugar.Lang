#ifndef BUILT_IN_FUNCTION_H
#define BUILT_IN_FUNCTION_H

#include <vector>

#include "Interfaces/DataTypes/i_data_type.h"
#include "Interfaces/Creation/i_built_in_function.h"

namespace Analysis::Structure::Core
{
    class BuiltInFunction : public virtual Interfaces::IBuiltInFunction
    {
        private:
            std::vector<const Interfaces::IDataType*> parameters;

        public:
            [[nodiscard]] unsigned long ParameterCount() const override;
            [[nodiscard]] const Interfaces::IDataType* ParameterAt(unsigned long index) const override;

            void PushParameterType(const Interfaces::IDataType* type) override;
    };
}

#endif
