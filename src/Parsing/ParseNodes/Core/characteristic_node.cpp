#include "characteristic_node.h"

using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Core
{
    template <int childCount>
    CharacteristicNode<childCount>::CharacteristicNode(const DescriberNode* const describer, const ParseNode* const type, const IdentifierNode* const identifier) : DescribableNode<childCount>(describer), EntityNode<childCount>(type), NameableNode<childCount>(identifier)
    { }
}
