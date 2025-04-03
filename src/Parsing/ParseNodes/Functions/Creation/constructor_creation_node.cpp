#include "constructor_creation_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    ConstructorCreationNode::ConstructorCreationNode(const DescriberNode* const describer, const CompoundDeclarationNode* const parameters, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword), DescribableNode(describer), BodyNode(body)
    {
        AddChild(ChildCode::Parameters, parameters);
    }

    NodeType ConstructorCreationNode::NodeType() const { return NodeType::ConstructorDeclaration; }
}

