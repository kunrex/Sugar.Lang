#include "base_property_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    BasePropertyNode::BasePropertyNode(const DescriberNode* const describer, const ParseNode* type, const IdentifierNode* identifier, const GetNode* const get, const SetNode* const set) : ParseNode(), CharacteristicNode(describer, type, identifier), PropertyNode(get, set), index(identifier->Index())
    { }

    NodeType BasePropertyNode::NodeType() const { return NodeType::Property; }

    unsigned long BasePropertyNode::Index() const { return name->Index(); }
}
