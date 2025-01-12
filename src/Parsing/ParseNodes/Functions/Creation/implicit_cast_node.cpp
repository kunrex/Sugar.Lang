#include "implicit_cast_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    ImplicitCastNode::ImplicitCastNode(const DescriberNode* describer, const ParseNode* type, const CompoundDeclarationNode* parameters, const ParseNode* body, const Token& keyword) : KeywordFunctionNode(describer, type, parameters, body, keyword)
    { }

    NodeType ImplicitCastNode::NodeType() const { return NodeType::ImplicitDeclaration; }
}
