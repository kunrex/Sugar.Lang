#include "characteristic_node.h"

namespace ParseNodes::Core
{
    CharacteristicNode::CharacteristicNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier) : DescribableNode(describer), NameableNode(identifier), EntityNode(type)
    { }
}