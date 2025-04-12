#include "scope_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    ScopeNode::ScopeNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType ScopeNode::NodeType() const { return NodeType::Scope; }

    void ScopeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Scope Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
