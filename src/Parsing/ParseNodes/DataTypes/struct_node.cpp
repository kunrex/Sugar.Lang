#include "struct_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::DataTypes
{
    StructNode::StructNode(const DescriberNode* const describer, const IdentifierNode* const identifier, const NodeCollection<ParseNode>* const body, const Token& keyword) : DataTypeNode(describer, identifier, body, keyword)
    { }

    NodeType StructNode::NodeType() const { return NodeType::Struct; }
}

