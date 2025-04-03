#include "explicit_cast_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    ExplicitCastNode::ExplicitCastNode(const DescriberNode* const describer, const ParseNode* const type, const CompoundDeclarationNode* const parameters, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword), FunctionNode(describer, type, parameters, body)
    { }

    NodeType ExplicitCastNode::NodeType() const { return NodeType::ExplicitDeclaration; }
}
