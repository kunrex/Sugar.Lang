#include "statement_collection_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    ExpressionListNode::ExpressionListNode() : NodeCollection()
    { }

    NodeType ExpressionListNode::NodeType() const { return NodeType::StatementCollection; }
}
