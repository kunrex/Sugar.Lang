#include "accessor_node.h"

using namespace Tokens;

using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    AccessorNode::AccessorNode(const DescriberNode* describer, const ParseNode* body, const Token& keyword) : ParseNode(), DescribableNode(describer), BodyNode(body), keyword(keyword)
    { }

    const Token& AccessorNode::Keyword() const { return keyword; }
}
