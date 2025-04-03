#include "entity_node.h"

#include "../parse_node.h"
#include "../Enums/child_code.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Core
{
    template <int childCount>
    EntityNode<childCount>::EntityNode(const ParseNode* const type)
    {
        FixedNodeCollection<childCount>::AddChild(ChildCode::Type, type);
    }
}
