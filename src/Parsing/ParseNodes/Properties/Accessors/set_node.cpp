#include "set_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    SetNode::SetNode(const DescriberNode* const describer, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : AccessorNode(describer, body, keyword)
    { }

    NodeType SetNode::NodeType() const { return NodeType::Set; }
}
