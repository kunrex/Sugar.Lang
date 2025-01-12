#include "declaration_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Statements
{
    DeclarationNode::DeclarationNode(const DescriberNode* describer, const ParseNode* type, const IdentifierNode* identifier, const Token& separator) : StatementNode(separator), CharacteristicNode(describer, type, identifier)
    { }

    NodeType DeclarationNode::NodeType() const { return NodeType::Declaration; }
}
