#include "binary_context_node.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    BinaryContextNode::BinaryContextNode(const IDataType* const creationType, const ContextNode* const lhs, const ContextNode* const rhs) : ContextNode(creationType), lhs(lhs), rhs(rhs)
    { }

    const ContextNode* BinaryContextNode::LHS() const { return lhs; }
    const ContextNode* BinaryContextNode::RHS() const { return rhs; }

    BinaryContextNode::~BinaryContextNode()
    {
        delete lhs;
        delete rhs;
    }
}

