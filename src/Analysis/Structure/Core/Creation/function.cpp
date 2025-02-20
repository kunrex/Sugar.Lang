#include "function.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    Function::Function(const Enums::Describer describer, const DataType* const creationType) : GlobalNode(), Describable(describer), Created(creationType), fullName()
    { }
}
