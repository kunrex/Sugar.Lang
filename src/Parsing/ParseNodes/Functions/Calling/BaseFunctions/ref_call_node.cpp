#include "ref_call_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    RefCallNode::RefCallNode(const Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType RefCallNode::NodeType() const { return NodeType::RefCall; }
}