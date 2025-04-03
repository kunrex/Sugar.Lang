#include "function_creation_node.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    FunctionCreationNode::FunctionCreationNode(const DescriberNode* const describer, const ParseNode* const type, const IdentifierNode* const identifier, const CompoundDeclarationNode* const parameters, const DynamicNodeCollection* const body) : FixedNodeCollection(identifier->Token()), FunctionNode(describer, type, parameters, body), NameableNode(identifier)
    { }

    NodeType FunctionCreationNode::NodeType() const { return NodeType::FunctionDeclaration; }
}
