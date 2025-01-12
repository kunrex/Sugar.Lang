#include "elif_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Conditions
{
    ElifNode::ElifNode(const ParseNode* condition, const ParseNode* body, const Token& keyword) : ConditionNode(condition, body, keyword)
    { }

    NodeType ElifNode::NodeType() const { return NodeType::ElseIf; }
}
