#include "built_in_void.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInVoid::BuiltInVoid(const string& name, const Enums::Describer describer) : VoidDefinition(name, describer)
    { }
}
