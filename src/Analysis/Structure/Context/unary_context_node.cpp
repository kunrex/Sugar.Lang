#include "unary_context_node.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    UnaryContextNode::UnaryContextNode(const IDataType* const creationType, const ContextNode* const operand) : ContextNode(creationType), operand(operand)
    { }

    const ContextNode* UnaryContextNode::Operand() const { return operand; }

    UnaryContextNode::~UnaryContextNode()
    {
        delete operand;
    }
}