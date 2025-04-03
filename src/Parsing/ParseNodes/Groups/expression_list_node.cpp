#include "expression_list_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    ExpressionListNode::ExpressionListNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType ExpressionListNode::NodeType() const { return NodeType::ExpressionList; }
}
