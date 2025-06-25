#include "data_type.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    DataType::DataType(const std::string& name, const Enums::Describer describer) : Nameable(name), Describable(describer)
    { }
}
