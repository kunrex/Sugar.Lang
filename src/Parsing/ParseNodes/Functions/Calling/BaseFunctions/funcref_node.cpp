#include "funcref_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    FuncRefNode::FuncRefNode(const Tokens::Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType FuncRefNode::NodeType() const { return NodeType::FuncRef; }
}