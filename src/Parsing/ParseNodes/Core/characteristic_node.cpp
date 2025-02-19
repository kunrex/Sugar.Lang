#include "characteristic_node.h"

using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Core
{
    CharacteristicNode::CharacteristicNode(const DescriberNode* const describer, const ParseNode* const type, const IdentifierNode* const identifier) : DescribableNode(describer), EntityNode(type), NameableNode(identifier)
    { }
}