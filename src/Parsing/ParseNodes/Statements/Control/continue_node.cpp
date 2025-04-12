#include "continue_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ContinueNode::ContinueNode(const Tokens::Token& separator) : ParseNode(separator)
    { }

    NodeType ContinueNode::NodeType() const { return NodeType::Continue; }

    void ContinueNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Continue Statement Node" << std::endl;
    }
}

