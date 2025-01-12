#include "break_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    BreakNode::BreakNode(const Token& separator) : StatementNode(separator)
    { }

    NodeType BreakNode::NodeType() const { return NodeType::Break; }
}
