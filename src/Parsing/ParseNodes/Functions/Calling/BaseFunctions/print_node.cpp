#include "print_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    PrintNode::PrintNode(const Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType PrintNode::NodeType() const { return NodeType::Print; }
}

