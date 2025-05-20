#include "built_in_function.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    unsigned long BuiltInFunction::ParameterCount() const { return parameters.size(); }

    const IDataType* BuiltInFunction::ParameterAt(const unsigned long index) const
    {
        return parameters.at(index);
    }

    void BuiltInFunction::PushParameterType(const IDataType* type)
    {
        parameters.push_back(type);
    }
}
