#include "characteristic.h"

using namespace std;

using namespace ParseNodes;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Characteristic::Characteristic(const string& name, const Enums::Describer describer, const IDataType* const creationType, const ParseNodes::ParseNode* const parseNode) : Variable(name, describer, creationType), fullName(), parseNode(parseNode)
    { }

    const ParseNode* Characteristic::ParseNode() const { return parseNode; }
}
