#include "variable.h"

using namespace std;

namespace Analysis::Structure::Core
{
    Variable::Variable(const string& name, const Enums::Describer describer, const DataType* const creationType) : Nameable(name), Describable(describer), Created(creationType)
    { }
}

