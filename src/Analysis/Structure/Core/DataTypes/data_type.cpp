#include "data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Core
{
    DataType::DataType(const string& name, const Enums::Describer describer) : Nameable(name), Describable(describer)
    { }
}
