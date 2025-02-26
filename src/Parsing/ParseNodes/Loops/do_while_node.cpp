#include "do_while_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Loops
{
    DoWhileNode::DoWhileNode(const ParseNode* const condition, const NodeCollection<ParseNode>* const body, const Token& keyword) : LoopNode(condition, body, keyword)
    { }

    NodeType DoWhileNode::NodeType() const { return NodeType::DoWhile; }
}
