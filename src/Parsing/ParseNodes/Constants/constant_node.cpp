#include "constant_node.h"

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;

namespace ParseNodes::Constants
{
    ConstantNode::ConstantNode(const Tokens::Token& token) : ParseNode(token)
    { }

    NodeType ConstantNode::NodeType() const { return NodeType::Constant; }

    void ConstantNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Constant Node" << std::endl;
    }
}
