#include "characteristic.h"

using namespace std;

using namespace ParseNodes;

namespace Analysis::Structure::Core
{
    Characteristic::Characteristic(const string& name, const Enums::Describer describer, const DataType* const creationType, const ParseNodes::ParseNode* const parseNode) : Variable(name, describer, creationType), parseNode(parseNode)
    { }

    const ParseNode* Characteristic::ParseNode() const { return parseNode; }
}
