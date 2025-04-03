#include "print_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    PrintNode::PrintNode(const Tokens::Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType PrintNode::NodeType() const { return NodeType::Print; }

    PrintlnNode::PrintlnNode(const Tokens::Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType PrintlnNode::NodeType() const { return NodeType::Println; }
}

