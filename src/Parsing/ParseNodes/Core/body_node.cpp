#include "body_node.h"

using namespace ParseNodes;

namespace ParseNodes::Core
{
    BodyNode::BodyNode(const NodeCollection<ParseNode>* const body) : body(body)
    { }

    const NodeCollection<ParseNode>* BodyNode::Body() const { return body; }

    BodyNode::~BodyNode()
    {
        delete body;
    }
}
