#include "value_node.h"

using namespace Tokens;

namespace ParseNodes::Values
{
    ValueNode::ValueNode(const Tokens::Token& token) : token(token)
    { }

    const Token& ValueNode::Token() const { return token; }
}
