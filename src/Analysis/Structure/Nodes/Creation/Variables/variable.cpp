#include "variable.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Creation
{
    Variable::Variable(const string& name, const Enums::Describer describer, const DataType* creationType) : Characteristic(name, describer, creationType)
    { }

    bool Variable::Readable() const { return true; }
    bool Variable::Writable() const { return !CheckDescriber(Describer::Const); }
}
