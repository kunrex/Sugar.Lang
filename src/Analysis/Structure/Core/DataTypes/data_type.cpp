#include "data_type.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    DataType::DataType(const std::string& name, const Enums::Describer describer) : ConstantChild(), Nameable(name), Describable(describer)
    { }

    const std::string& DataType::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "." + name;

        return  fullName;
    }
}
