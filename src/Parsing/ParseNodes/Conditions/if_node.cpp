#include "if_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Conditions
{
    IfNode::IfNode(const ParseNode* const condition, const NodeCollection<ParseNode>* const body, const Token& keyword) : ConditionNode(condition, body, keyword)
    { }

    NodeType IfNode::NodeType() const { return NodeType::If; }
}
