#include "throw_statement_node.h"

#include "../Enums/child_code.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ThrowStatementNode::ThrowStatementNode(const IParseNode* const exception, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Expression, exception);
    }

    NodeType ThrowStatementNode::NodeType() const { return NodeType::Throw; }

    void ThrowStatementNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Throw Statement Node" << std::endl;

        GetChild(static_cast<int>(ChildCode::Expression))->Print(indent + (last ? " " : "| "), true);
    }
}
