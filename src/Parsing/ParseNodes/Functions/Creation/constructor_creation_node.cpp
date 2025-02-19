#include "constructor_creation_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    ConstructorCreationNode::ConstructorCreationNode(const DescriberNode* const describer, const CompoundDeclarationNode* const parameters, const ScopeNode* const body, const Token& keyword) : KeywordFunctionNode(describer, nullptr, parameters, body, keyword)
    { }

    NodeType ConstructorCreationNode::NodeType() const { return NodeType::ConstructorDeclaration; }
}

