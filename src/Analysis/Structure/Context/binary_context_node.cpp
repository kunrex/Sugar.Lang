#include "binary_context_node.h"

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    BinaryContextNode::BinaryContextNode(const IDataType* const creationType, const IContextNode* const lhs, const IContextNode* const rhs) : FixedContextCollection<2>(creationType)
    {
        AddChild(ChildCode::LHS, lhs);
        AddChild(ChildCode::RHS, rhs);
    }
}

