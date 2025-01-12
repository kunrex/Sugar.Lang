#include "built_in_data_type.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Wrappers
{
    BuiltInDataType::BuiltInDataType(std::string name) : DataType(name, Describer::Public)
    {

    }
}
