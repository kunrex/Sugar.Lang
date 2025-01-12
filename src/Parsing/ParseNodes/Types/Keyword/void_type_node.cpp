#include "void_type_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    VoidTypeNode::VoidTypeNode(const Tokens::Token& keyword) : KeywordTypeNode(keyword)
    { }

    NodeType VoidTypeNode::NodeType() const { return NodeType::VoidType; }
}