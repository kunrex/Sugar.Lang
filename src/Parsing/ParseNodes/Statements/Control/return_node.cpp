#include "return_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ReturnNode::ReturnNode(const Tokens::Token& separator) : FixedNodeCollection(separator)
    {
        AddChild(ChildCode::Expression, nullptr);
    }

    ReturnNode::ReturnNode(const IParseNode* const value, const Tokens::Token& separator) : FixedNodeCollection(separator)
    {
        AddChild(ChildCode::Expression, value);
    }

    NodeType ReturnNode::NodeType() const { return NodeType::Return; }

    void ReturnNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Return Statement Node" << std::endl;

        if (const auto expression = GetChild(static_cast<int>(ChildCode::Expression)); expression != nullptr)
            expression->Print(indent + (last ? " " : "| "), true);
    }

}
