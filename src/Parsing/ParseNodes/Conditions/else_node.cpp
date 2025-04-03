#include "else_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Conditions
{
    ElseNode::ElseNode(const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Body, body);
    }

    NodeType ElseNode::NodeType() const { return NodeType::Else; }
}
