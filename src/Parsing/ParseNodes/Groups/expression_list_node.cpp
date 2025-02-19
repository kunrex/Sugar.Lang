#include "expression_list_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    ExpressionListNode::ExpressionListNode(const unsigned long index) : NodeCollection(), index(index)
    { }

    NodeType ExpressionListNode::NodeType() const { return NodeType::ExpressionList; }

    unsigned long ExpressionListNode::Index() const { return index; }
}
