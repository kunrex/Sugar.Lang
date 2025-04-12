#include "dictionary_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    DictionaryTypeNode::DictionaryTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType DictionaryTypeNode::NodeType() const { return NodeType::DictionaryType; }

    void DictionaryTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Dictionary Type Node" << std::endl;
        const auto next = indent + (last ? " " : "| ");

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(next, ++i == childCount);
    }
}