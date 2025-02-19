#include "enum_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::DataTypes
{
    EnumNode::EnumNode(const DescriberNode* const describer, const IdentifierNode* const identifier, const NodeCollection<ParseNode>* const body, const Token& keyword) : DataTypeNode(describer, identifier, body, keyword)
    { }

    NodeType EnumNode::NodeType() const { return NodeType::Enum; }
}
