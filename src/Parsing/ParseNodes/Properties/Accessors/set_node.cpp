#include "set_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    SetNode::SetNode(const DescriberNode* describer, const ParseNode* body, const Token& keyword) : AccessorNode(describer, body, keyword)
    { }

    NodeType SetNode::NodeType() const { return NodeType::Set; }
}
