#include "property_definition.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    PropertyDefinition::PropertyDefinition(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const parseNode) : Characteristic(name, describer, creationType, parseNode)
    { }
}

