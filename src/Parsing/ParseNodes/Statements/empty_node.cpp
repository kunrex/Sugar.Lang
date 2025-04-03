#include "empty_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    EmptyNode::EmptyNode(const Tokens::Token& separator) : ParseNode(separator)
    { }

    NodeType EmptyNode::NodeType() const { return NodeType::Empty; }
}
