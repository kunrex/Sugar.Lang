#include "anonymous_type_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    AnonymousTypeNode::AnonymousTypeNode(const Tokens::Token& keyword) : ParseNode(keyword)
    { }

    NodeType AnonymousTypeNode::NodeType() const { return NodeType::AnonymousType; }

    void AnonymousTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Anonymous Type Node" << std::endl;
    }
}