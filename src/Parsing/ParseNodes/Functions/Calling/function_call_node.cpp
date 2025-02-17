#include "function_call_node.h"

#include <vector>

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;

namespace ParseNodes::Functions::Calling
{
    FunctionCallNode::FunctionCallNode(const IdentifierNode* identifier) : NodeCollection(), identifier(identifier)
    { }

    NodeType FunctionCallNode::NodeType() const { return NodeType::FunctionCall; }

    unsigned long FunctionCallNode::Index() const { return identifier->Index(); }

    FunctionCallNode::~FunctionCallNode()
    {
        delete identifier;
    }
}
