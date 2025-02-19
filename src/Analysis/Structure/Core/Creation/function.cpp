#include "function.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    Function::Function(const Enums::Describer describer, const DataType* const creationType) : Describable(describer), Created(creationType), GlobalNode()
    { }

    bool Function::Readable() const { return true; }
    bool Function::Writable() const { return false; }
}
