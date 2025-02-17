#include "function_creation_node.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    FunctionCreationNode::FunctionCreationNode(const DescriberNode* describer, const ParseNode* type, const IdentifierNode* identifier, const CompoundDeclarationNode* parameters, const ScopeNode* body) : ParseNode(), FunctionNode(describer, type, parameters, body), NameableNode(identifier), index(identifier->Index())
    { }

    NodeType FunctionCreationNode::NodeType() const { return NodeType::FunctionDeclaration; }

    unsigned long FunctionCreationNode::Index() const { return name->Index(); }
}
