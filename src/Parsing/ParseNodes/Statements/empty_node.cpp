#include "empty_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    EmptyNode::EmptyNode(const Token& separator) : StatementNode(separator)
    { }

    NodeType EmptyNode::NodeType() const { return NodeType::Empty; }
}
