#include "built_in_type_node.h"

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    BuiltInTypeNode::BuiltInTypeNode(const Tokens::Token& keyword) : KeywordTypeNode(keyword)
    { }

    SyntaxKind BuiltInTypeNode::Kind() const { return keyword.Kind(); }

    NodeType BuiltInTypeNode::NodeType() const { return NodeType::BuiltInType; }
}
