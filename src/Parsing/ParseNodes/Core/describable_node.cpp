#include "describable_node.h"

#include "../Enums/child_code.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Describers;

namespace ParseNodes::Core
{
    template <int childCount>
    DescribableNode<childCount>::DescribableNode(const DescriberNode* const describer)
    {
        FixedNodeCollection<childCount>::AddChild(ChildCode::Describer, describer);
    }
}
