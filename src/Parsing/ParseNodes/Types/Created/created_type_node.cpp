#include "created_type_node.h"

using namespace std;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;

namespace ParseNodes::Types
{
    CreatedTypeNode::CreatedTypeNode(const IdentifierNode* const identifier) : ParseNode(identifier->Token())
    { }

    NodeType CreatedTypeNode::NodeType() const { return NodeType::CreatedType; }

    void CreatedTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Created Type Node: " << *token.Value<string>() << std::endl;
    }
}