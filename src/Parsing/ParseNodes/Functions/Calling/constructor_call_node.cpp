#include "constructor_call_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    ConstructorCallNode::ConstructorCallNode(const ParseNode* const type, const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    {
        AddChild(type);
    }

    NodeType ConstructorCallNode::NodeType() const { return NodeType::ConstructorCall; }
}
