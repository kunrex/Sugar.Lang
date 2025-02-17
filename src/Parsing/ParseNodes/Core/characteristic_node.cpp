#include "characteristic_node.h"

using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Core
{
    CharacteristicNode::CharacteristicNode(const DescriberNode* describer, const ParseNode* type, const IdentifierNode* identifier) : DescribableNode(describer), EntityNode(type), NameableNode(identifier)
    { }
}