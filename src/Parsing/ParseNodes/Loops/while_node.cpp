#include "while_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Loops
{
    WhileNode::WhileNode(const ParseNode* const condition, const ScopeNode* const body, const Token& keyword) : LoopNode(condition, body, keyword)
    { }

    NodeType WhileNode::NodeType() const { return NodeType::While;}
}
