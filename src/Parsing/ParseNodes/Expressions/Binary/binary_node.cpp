#include "binary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    BinaryNode::BinaryNode(const Tokens::Token& base, const ParseNode* const lhs, const ParseNode* const rhs) : FixedNodeCollection<2>(base)
    {
        AddChild(ChildCode::LHS, lhs);
        AddChild(ChildCode::RHS, rhs);
    }

    NodeType BinaryNode::NodeType() const { return NodeType::Binary; }
}
