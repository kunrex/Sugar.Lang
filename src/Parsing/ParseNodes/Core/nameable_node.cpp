#include "nameable_node.h"

#include "../Enums/child_code.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;

namespace ParseNodes::Core
{
    template <int childCount>
    NameableNode<childCount>::NameableNode(const IdentifierNode* const identifier)
    {
        FixedNodeCollection<childCount>::AddChild(ChildCode::Identifier, identifier);;
    }
}
