#include "unary_context_node.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Context
{
    UnaryContextNode::UnaryContextNode(const DataType* creationType, const ContextNode* operand) : ContextNode(creationType), operand(operand)
    { }

    const ContextNode* UnaryContextNode::Operand() const { return operand; }

    UnaryContextNode::~UnaryContextNode()
    {
        delete operand;
    }
}