#include "this_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Values
{
    ThisNode::ThisNode(const Tokens::Token& keyword) : ParseNode(keyword)
    { }

    NodeType ThisNode::NodeType() const { return NodeType::This; }

    void ThisNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "This Node" << std::endl;
    }

}