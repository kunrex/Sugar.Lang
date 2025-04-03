#include "identifier_node.h"

using namespace std;

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Values
{
    IdentifierNode::IdentifierNode(const Tokens::Token& identifier) : ParseNode(identifier)
    { }

    NodeType IdentifierNode::NodeType() const { return NodeType::Identifier; }
}