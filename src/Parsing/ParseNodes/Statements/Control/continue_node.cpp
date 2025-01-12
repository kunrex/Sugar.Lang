#include "continue_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ContinueNode::ContinueNode(const Token& separator) : StatementNode(separator)
    { }

    NodeType ContinueNode::NodeType() const { return NodeType::Continue; }
}

