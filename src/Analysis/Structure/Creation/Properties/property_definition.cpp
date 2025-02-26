#include "property_definition.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    PropertyDefinition::PropertyDefinition(const string& name, const Enums::Describer describer, const IDataType* const creationType, const ParseNodes::ParseNode* const parseNode) : Characteristic(name, describer, creationType, parseNode), PropertySignature()
    { }
}

