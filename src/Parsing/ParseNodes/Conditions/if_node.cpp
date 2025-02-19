#include "if_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Conditions
{
    IfNode::IfNode(const ParseNode* const condition, const ScopeNode* const body, const Token& keyword) : ConditionNode(condition, body, keyword)
    { }

    NodeType IfNode::NodeType() const { return NodeType::If; }
}
