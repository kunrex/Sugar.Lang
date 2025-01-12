#include "property_set.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Global
{
    PropertySet::PropertySet(const string& name, const Enums::Describer describer, const DataType* creationType, Creation::Set* const set) : Property(name, describer, creationType), Setable(set)
    { }
}
