#include "do_while_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Loops
{
    DoWhileNode::DoWhileNode(const ParseNode* const condition, const ScopeNode* const body, const Token& keyword) : LoopNode(condition, body, keyword)
    { }

    NodeType DoWhileNode::NodeType() const { return NodeType::DoWhile; }
}
