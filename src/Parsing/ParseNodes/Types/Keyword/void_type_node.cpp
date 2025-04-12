#include "void_type_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    VoidTypeNode::VoidTypeNode(const Tokens::Token& keyword) : ParseNode(keyword)
    { }

    NodeType VoidTypeNode::NodeType() const { return NodeType::VoidType; }

    void VoidTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Void Node" << std::endl;
    }
}