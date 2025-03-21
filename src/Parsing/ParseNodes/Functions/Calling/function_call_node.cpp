#include "function_call_node.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;

namespace ParseNodes::Functions::Calling
{
    FunctionCallNode::FunctionCallNode(const IdentifierNode* const identifier) : NodeCollection(), identifier(identifier)
    { }

    NodeType FunctionCallNode::NodeType() const { return NodeType::FunctionCall; }

    unsigned long FunctionCallNode::Index() const { return identifier->Index(); }

    const IdentifierNode* FunctionCallNode::Identifier() const { return identifier;}

    FunctionCallNode::~FunctionCallNode()
    {
        delete identifier;
    }
}
