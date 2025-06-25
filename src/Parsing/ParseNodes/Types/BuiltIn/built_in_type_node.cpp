#include "built_in_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    BuiltInTypeNode::BuiltInTypeNode(const Tokens::Token& keyword) : ParseNode(keyword)
    { }

    NodeType BuiltInTypeNode::NodeType() const { return NodeType::BuiltInType; }

    void BuiltInTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Built-In Type Node: " << ToString(token.Kind()) << std::endl;
    }
}