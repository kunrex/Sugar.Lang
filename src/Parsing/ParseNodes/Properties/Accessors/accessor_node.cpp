#include "accessor_node.h"

using namespace Tokens;

using namespace ParseNodes;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    AccessorNode::AccessorNode(const DescriberNode* const describer, const NodeCollection<ParseNode>* const body, const Token& keyword) : ParseNode(), DescribableNode(describer), BodyNode(body), keyword(keyword)
    { }

    unsigned long AccessorNode::Index() const { return keyword.Index(); }
}
