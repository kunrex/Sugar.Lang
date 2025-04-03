#include "function_node.h"

#include "../Enums/child_code.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Core
{
    template <int childCount>
    FunctionNode<childCount>::FunctionNode(const DescriberNode* const describer, const ParseNode* const type, const CompoundDeclarationNode* const parameters, const DynamicNodeCollection* const body) : DescribableNode<childCount>(describer), EntityNode<childCount>(type), BodyNode<childCount>(body)
    {
        FixedNodeCollection<childCount>::AddChild(ChildCode::Parameters, parameters);
    }
}
