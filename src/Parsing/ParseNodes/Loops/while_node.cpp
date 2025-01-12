#include "while_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Loops
{
    WhileNode::WhileNode(const ParseNode* condition, const ParseNode* body, const Token& keyword) : LoopNode(condition, body, keyword)
    { }

    NodeType WhileNode::NodeType() const { return NodeType::While;}
}
