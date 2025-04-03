#include "base_function_call_node.h"

using namespace Tokens;

namespace ParseNodes::Functions::Calling
{
    BaseFunctionCallNode::BaseFunctionCallNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }
}
