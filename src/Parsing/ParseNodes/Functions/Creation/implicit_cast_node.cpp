#include "implicit_cast_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    ImplicitCastNode::ImplicitCastNode(const DescriberNode* const describer, const ParseNode* const type, const CompoundDeclarationNode* const parameters, const NodeCollection<ParseNode>* const body, const Token& keyword) : KeywordFunctionNode(describer, type, parameters, body, keyword)
    { }

    NodeType ImplicitCastNode::NodeType() const { return NodeType::ImplicitDeclaration; }
}
