#include "else_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Conditions
{
    ElseNode::ElseNode(const ParseNode* body, const Token& keyword) : ConditionNode(nullptr, body, keyword)
    { }

    NodeType ElseNode::NodeType() const { return NodeType::Else; }
}
