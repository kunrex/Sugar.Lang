#include "body_node.h"

namespace ParseNodes::Core
{
    BodyNode::BodyNode(const ParseNode* body) : body(body)
    { }

    const ParseNode* BodyNode::Body() const { return body; }

    BodyNode::~BodyNode()
    {
        delete body;
    }
}
