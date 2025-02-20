#include "enum_constant.h"

#include "../../Wrappers/Value/integer.h"

using namespace std;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Global
{
    EnumConstant::EnumConstant(const string& name) : GlobalVariable(name, Describer::PublicStatic, &Integer::Instance(), nullptr)
    { }

    EnumConstant::EnumConstant(const string& name, const ParseNodes::ParseNode* const value) : GlobalVariable(name, Describer::PublicStatic, &Integer::Instance(), value)
    { }

    bool EnumConstant::Readable() const { return true; }
    bool EnumConstant::Writable() const { return false; }
}
