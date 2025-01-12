#include "property_get_set.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Global
{
    PropertyGetSet::PropertyGetSet(const string& name, const Enums::Describer describer, const DataType* creationType, Creation::Get* const get, Creation::Set* const set) : Property(name, describer, creationType), GetSet(get, set)
    { }
}
