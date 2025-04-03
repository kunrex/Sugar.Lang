#include "return_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ReturnNode::ReturnNode(const Tokens::Token& separator) : FixedNodeCollection(separator)
    {
        AddChild(ChildCode::Expression, nullptr);
    }

    ReturnNode::ReturnNode(const ParseNode* const value, const Tokens::Token& separator) : FixedNodeCollection(separator)
    {
        AddChild(ChildCode::Expression, value);
    }

    NodeType ReturnNode::NodeType() const { return NodeType::Return; }
}
