#include "class_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::DataTypes
{
    ClassNode::ClassNode(const DescriberNode* describer, const IdentifierNode* identifier, const NodeCollection<ParseNode>* body, const Token& keyword) : DataTypeNode(describer, identifier, body, keyword)
    { }

    NodeType ClassNode::NodeType() const { return NodeType::Class; }
}
