#include "built_in_function.h"

namespace Analysis::Structure::Core::Interfaces
{
    unsigned long BuiltInFunction::ParameterCount() const { return parameters.size(); }

    const IDataType* BuiltInFunction::ParameterAt(unsigned long index) const
    {
        return parameters.at(index);
    }

    void BuiltInFunction::PushParameterType(const IDataType* type)
    {
        parameters.push_back(type);
    }
}
