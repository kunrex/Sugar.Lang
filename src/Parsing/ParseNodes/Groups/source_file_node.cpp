#include "source_file_node.h"

using namespace Tokens;
using namespace Tokens::Enums;

using namespace ParseNodes::Enums;

const auto startOfFile = Token(0, TokenType::Constant, SyntaxKind::Constant, 0l);

namespace ParseNodes::Groups
{
    SourceFileNode::SourceFileNode() : DynamicNodeCollection(startOfFile)
    { }

    NodeType SourceFileNode::NodeType() const { return NodeType::Source; }

    void SourceFileNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Source File Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
