#include "declaration_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Statements
{
    DeclarationNode::DeclarationNode(const DescriberNode* const describer, const ParseNode* const type, const IdentifierNode* const identifier, const Tokens::Token& separator) : FixedNodeCollection(separator), CharacteristicNode(describer, type, identifier)
    { }

    NodeType DeclarationNode::NodeType() const { return NodeType::Declaration; }
}
