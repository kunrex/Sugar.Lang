#include "enum_field.h"

#include "../../Wrappers/Value/integer.h"

using namespace std;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    EnumField::EnumField(const string& name) : GlobalVariable(name, Describer::PublicStatic, &Integer::Instance(), nullptr)
    { }

    EnumField::EnumField(const string& name, const ParseNodes::ParseNode* const value) : GlobalVariable(name, Describer::PublicStatic, &Integer::Instance(), value)
    { }

    bool EnumField::Writable() const { return false; }
}
