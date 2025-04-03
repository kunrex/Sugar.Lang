#ifndef BASE_FUNCTION_CALL_NODE_H
#define BASE_FUNCTION_CALL_NODE_H

#include "../../../parse_node.h"
#include "../../../../../Lexing/Tokens/token.h"

namespace ParseNodes::Functions::Calling
{
    class BaseFunctionCallNode : public DynamicNodeCollection
    {
        public:
            explicit BaseFunctionCallNode(const Tokens::Token& keyword);
    };
}

#endif
