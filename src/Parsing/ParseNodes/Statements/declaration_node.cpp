#include "declaration_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Statements
{
    DeclarationNode::DeclarationNode(const DescriberNode* const describer, const ParseNode* const type, const IdentifierNode* const identifier, const Token& separator) : StatementNode(separator), CharacteristicNode(describer, type, identifier)
    { }

    NodeType DeclarationNode::NodeType() const { return NodeType::Declaration; }

    unsigned long DeclarationNode::Index() const { return name->Index(); }
}
