#include "function.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Function::Function(const Enums::Describer describer, const IDataType* const creationType) : GlobalNode(), Describable(describer), Created(creationType), fullName()
    { }
}
