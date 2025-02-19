#include "else_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Conditions
{
    ElseNode::ElseNode(const ScopeNode* const body, const Token& keyword) : ConditionNode(nullptr, body, keyword)
    { }

    NodeType ElseNode::NodeType() const { return NodeType::Else; }
}
