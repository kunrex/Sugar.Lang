#include "binary_context_node.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Context
{
    BinaryContextNode::BinaryContextNode(const DataType* creationType, const ContextNode* lhs, const ContextNode* rhs) : ContextNode(creationType), lhs(lhs), rhs(rhs)
    { }

    const ContextNode* BinaryContextNode::LHS() const { return lhs; }
    const ContextNode* BinaryContextNode::RHS() const { return rhs; }

    bool BinaryContextNode::Readable() const { return true; }
    bool BinaryContextNode::Writable() const { return false; }

    BinaryContextNode::~BinaryContextNode()
    {
        delete lhs;
        delete rhs;
    }
}

