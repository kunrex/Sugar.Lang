#include "identifier_node.h"

using namespace std;

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Values
{
    IdentifierNode::IdentifierNode(const Token& identifier) : ValueNode(identifier)
    { }

    NodeType IdentifierNode::NodeType() const { return NodeType::Identifier; }

    string IdentifierNode::Value() const { return *token.Value<std::string>(); }
}
