#include "accessor_node.h"

using namespace Tokens;

using namespace ParseNodes;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    AccessorNode::AccessorNode(const DescriberNode* const describer, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword), DescribableNode(describer), BodyNode(body)
    { }
}
