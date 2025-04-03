#include "break_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    BreakNode::BreakNode(const Tokens::Token& separator) : ParseNode(separator)
    { }

    NodeType BreakNode::NodeType() const { return NodeType::Break; }
}
