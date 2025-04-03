#include "if_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Conditions
{
    IfNode::IfNode(const ParseNode* const condition, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Expression, condition);
        AddChild(ChildCode::Body, body);
    }

    NodeType IfNode::NodeType() const { return NodeType::If; }
}
