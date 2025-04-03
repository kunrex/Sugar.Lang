#include "base_property_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    BasePropertyNode::BasePropertyNode(const DescriberNode* const describer, const ParseNode* type, const IdentifierNode* identifier, const GetNode* const get, const SetNode* const set) : FixedNodeCollection(identifier->Token()), DescribableNode(describer), EntityNode(type), NameableNode(identifier), PropertyNode(get, set)
    { }

    NodeType BasePropertyNode::NodeType() const { return NodeType::Property; }
}
