#include "input_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    InputNode::InputNode(const Tokens::Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType InputNode::NodeType() const { return NodeType::Input; }
}
