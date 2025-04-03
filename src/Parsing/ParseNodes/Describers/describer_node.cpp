#include "describer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Describers
{
    DescriberNode::DescriberNode(const Tokens::Token& openBracket) : DynamicNodeCollection(openBracket)
    { }

    NodeType DescriberNode::NodeType() const { return NodeType::Describer; }
}
