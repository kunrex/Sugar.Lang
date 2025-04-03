#include "function_call_node.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;

namespace ParseNodes::Functions::Calling
{
    FunctionCallNode::FunctionCallNode(const IdentifierNode* const identifier) : DynamicNodeCollection(identifier->Token())
    {
        AddChild(identifier);
    }

    NodeType FunctionCallNode::NodeType() const { return NodeType::FunctionCall; }
}
