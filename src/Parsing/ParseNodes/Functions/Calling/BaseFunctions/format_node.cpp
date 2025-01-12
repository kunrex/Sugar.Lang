#include "format_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    FormatNode::FormatNode(const Tokens::Token& keyword) :  BaseFunctionCallNode(keyword)
    { }

    NodeType FormatNode::NodeType() const { return NodeType::Format; }
}
