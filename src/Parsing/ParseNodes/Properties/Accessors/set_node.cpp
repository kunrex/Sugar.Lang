#include "set_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    SetNode::SetNode(const DescriberNode* const describer, const ScopeNode* const body, const Token& keyword) : AccessorNode(describer, body, keyword)
    { }

    NodeType SetNode::NodeType() const { return NodeType::Set; }
}
