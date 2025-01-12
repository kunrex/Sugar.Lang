#include "base_property_node.h"

#include "base_indexer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    BasePropertyNode::BasePropertyNode(const DescriberNode* describer, const ParseNode* type, const IdentifierNode* identifier, const GetNode* get, const SetNode* set) : ParseNode(), CharacteristicNode(describer, type, identifier), PropertyNode(get, set)
    { }

    NodeType BasePropertyNode::NodeType() const { return NodeType::Property; }
}
