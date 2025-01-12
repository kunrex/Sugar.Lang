#include "constant_node.h"

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;

namespace ParseNodes::Constants
{
    ConstantNode::ConstantNode(const Tokens::Token& token) : ParseNode(), token(token)
    { }

    NodeType ConstantNode::NodeType() const { return NodeType::Constant; }

    TypeKind ConstantNode::ConstantType() const { return static_cast<TypeKind>(token.Metadata()); }
}
