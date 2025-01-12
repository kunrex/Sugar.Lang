#include "base_function_call_node.h"

using namespace Tokens;

namespace ParseNodes::Functions::Calling
{
    BaseFunctionCallNode::BaseFunctionCallNode(const Token& keyword) : NodeCollection(), keyword(keyword)
    { }

    const Token& BaseFunctionCallNode::Keyword() const { return keyword; }
}
