#include "describable.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    Describable::Describable(const Describer describer) : describer(describer)
    { }

    bool Describable::ValidateDescriber(const Describer allowed) const { return (allowed & describer) == describer; }

    bool Describable::MatchDescriber(const Describer expected) const { return describer == expected; }
    bool Describable::CheckDescriber(const Describer describer) const { return (describer & this->describer) == describer; }
}
