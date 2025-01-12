#include "if_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Conditions
{
    IfNode::IfNode(const ParseNode* condition, const ParseNode* body, const Token& keyword) : ConditionNode(condition, body, keyword)
    { }

    NodeType IfNode::NodeType() const { return NodeType::If; }
}
