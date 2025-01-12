#include "void_definition.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    VoidDefinition::VoidDefinition(const string& name, const Enums::Describer describer) : FunctionDefinition(name, describer, nullptr)
    { }

    bool VoidDefinition::Readable() const { return false; }
}
