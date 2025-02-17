#include "body_node.h"

using namespace ParseNodes::Groups;

namespace ParseNodes::Core
{
    BodyNode::BodyNode(const ScopeNode* body) : body(body)
    { }

    const ScopeNode* BodyNode::Body() const { return body; }

    BodyNode::~BodyNode()
    {
        delete body;
    }
}
