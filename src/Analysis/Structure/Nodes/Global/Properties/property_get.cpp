#include "property_get.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Global
{
    PropertyGet::PropertyGet(const string& name, const Enums::Describer describer, const DataType* creationType, Creation::Get* get) : Property(name, describer, creationType), Getable(get)
    { }
}