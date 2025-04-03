#include "body_node.h"

#include "../Enums/child_code.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Core
{
    template <int childCount>
    BodyNode<childCount>::BodyNode(const DynamicNodeCollection* const body)
    {
        FixedNodeCollection<childCount>::AddChild(ChildCode::Body, body);
    }
}
