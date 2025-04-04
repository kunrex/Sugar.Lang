#include "unary_context_node.h"

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    UnaryContextNode::UnaryContextNode(const IDataType* const creationType, const IContextNode* const operand) : FixedContextCollection(creationType)
    {
        AddChild(ChildCode::Expression, operand);
    }
}