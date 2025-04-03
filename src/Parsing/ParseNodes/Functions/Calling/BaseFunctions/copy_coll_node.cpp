#include "copy_coll_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    CopyCallNode::CopyCallNode(const Tokens::Token& keyword) : BaseFunctionCallNode(keyword)
    { }

    NodeType CopyCallNode::NodeType() const { return NodeType::Copy; }
}