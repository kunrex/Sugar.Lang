#include "get_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    GetNode::GetNode(const DescriberNode* const describer, const ScopeNode* const body, const Token& keyword) : AccessorNode(describer, body, keyword)
    { }

    NodeType GetNode::NodeType() const { return NodeType::Get; }
}
