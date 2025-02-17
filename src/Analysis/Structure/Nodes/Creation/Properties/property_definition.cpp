#include "property_definition.h"

using namespace std;

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Creation
{
    PropertyDefinition::PropertyDefinition(const std::string& name, const Enums::Describer describer, const DataType* creationType) : GlobalNode(), Characteristic(name, describer, creationType)
    { }
}

