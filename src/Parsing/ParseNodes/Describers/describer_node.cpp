#include "describer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Describers
{
    DescriberNode::DescriberNode(const Tokens::Token& openBracket) : DynamicNodeCollection(openBracket)
    { }

    NodeType DescriberNode::NodeType() const { return NodeType::Describer; }

    void DescriberNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Describer Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
