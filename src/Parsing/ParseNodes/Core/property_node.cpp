#include "property_node.h"

#include "../Enums/child_code.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Properties;

namespace ParseNodes::Core
{
    template <int childCount>
    PropertyNode<childCount>::PropertyNode(const GetNode* const get, const SetNode* const set)
    {
        FixedNodeCollection<childCount>::AddChild(ChildCode::Get, get);
        FixedNodeCollection<childCount>::AddChild(ChildCode::Set, set);
    }
}
