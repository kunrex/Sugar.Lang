#include "null_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Values
{
    NullNode::NullNode(const Tokens::Token& keyword) : ParseNode(keyword)
    { }

    NodeType NullNode::NodeType() const { return NodeType::Null; }

    void NullNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Null Node" << std::endl;
    }
}