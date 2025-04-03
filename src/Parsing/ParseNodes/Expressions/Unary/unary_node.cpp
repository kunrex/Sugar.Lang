#include "unary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    UnaryNode::UnaryNode(const Tokens::Token& base, const ParseNode* const operand) : FixedNodeCollection(base)
    {
        AddChild(ChildCode::Expression, operand);
    }

    NodeType UnaryNode::NodeType() const { return NodeType::Unary; }
}
