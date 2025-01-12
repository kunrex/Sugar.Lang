#include "characteristic.h"

namespace Analysis::Structure::Core
{
    Characteristic::Characteristic(const std::string& name, const Enums::Describer describer, const DataType* creationType) : Nameable(name), Describable(describer), Created(creationType)
    { }

    bool Characteristic::operator<(const Characteristic& rhs) const
    {
        return name < rhs.name;
    }
}
