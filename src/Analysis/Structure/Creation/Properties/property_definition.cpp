#include "property_definition.h"

using namespace std;

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Creation
{
    PropertyDefinition::PropertyDefinition(const string& name, const Enums::Describer describer, const DataType* const creationType, const ParseNodes::ParseNode* const parseNode) : Characteristic(name, describer, creationType, parseNode), PropertySignature()
    { }
}

