#include "invoke_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    InvokeNode::InvokeNode(const Tokens::Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType InvokeNode::NodeType() const { return NodeType::Invoke; }
}
