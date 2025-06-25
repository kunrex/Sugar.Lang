#include "variable.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Variable::Variable(const std::string& name, const Enums::Describer describer, const IDataType* const creationType) : Nameable(name), Describable(describer), Created(creationType)
    { }
}

