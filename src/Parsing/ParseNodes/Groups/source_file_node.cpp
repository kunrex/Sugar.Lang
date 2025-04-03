#include "source_file_node.h"

using namespace Tokens;
using namespace Tokens::Enums;

using namespace ParseNodes::Enums;

const auto startOfFile = Token(0, TokenType::Constant, SyntaxKind::Constant, "");

namespace ParseNodes::Groups
{
    SourceFileNode::SourceFileNode() : DynamicNodeCollection(startOfFile)
    { }

    NodeType SourceFileNode::NodeType() const { return NodeType::Source; }
}
