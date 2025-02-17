#include "value_node.h"

using namespace Tokens;

namespace ParseNodes::Values
{
    ValueNode::ValueNode(const Tokens::Token& token) : token(token)
    { }

    unsigned long ValueNode::Index() const { return token.Index(); }
}
