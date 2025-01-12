#include "property.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    Property::Property(const string& name, Enums::Describer describer, const DataType* creationType) : Characteristic(name, describer, creationType)
    { }
}

