#include "function.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Function::Function(const Enums::Describer describer, const IDataType* const creationType) : Describable(describer), Created(creationType)
    { }
}
