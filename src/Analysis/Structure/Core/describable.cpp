#include "describable.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    Describable::Describable(const Describer describer) : describer(describer)
    { }

    bool Describable::ValidateDescriber(const Describer allowed) const { return (allowed & describer) == describer; }

    bool Describable::CheckDescriber(const Enums::Describer describer) const { return (describer & this->describer) == describer; }
    bool Describable::ValidateDescriber(const Enums::Describer allowed) const { return (allowed & describer) == describer; }
}
