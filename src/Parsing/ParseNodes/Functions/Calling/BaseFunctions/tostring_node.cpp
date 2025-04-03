#include "tostring_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    ToStringNode::ToStringNode(const Tokens::Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType ToStringNode::NodeType() const { return NodeType::ToString; }
}