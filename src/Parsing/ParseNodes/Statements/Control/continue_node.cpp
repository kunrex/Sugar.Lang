#include "continue_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ContinueNode::ContinueNode(const Tokens::Token& separator) : ParseNode(separator)
    { }

    NodeType ContinueNode::NodeType() const { return NodeType::Continue; }
}

