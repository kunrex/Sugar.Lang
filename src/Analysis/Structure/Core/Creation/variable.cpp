#include "variable.h"

#include "../DataTypes/data_type.h"

using namespace std;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Variable::Variable(const string& name, const Enums::Describer describer, const IDataType* const creationType) : Nameable(name), Describable(describer), Created(creationType)
    { }
}

