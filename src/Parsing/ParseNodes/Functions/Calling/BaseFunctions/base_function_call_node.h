#ifndef BASE_FUNCTION_CALL_NODE_H
#define BASE_FUNCTION_CALL_NODE_H

#include "../../../parse_node.h"
#include "../../../../../Lexing/Tokens/token.h"

namespace ParseNodes::Functions::Calling
{
    class BaseFunctionCallNode : public NodeCollection<ParseNode>
    {
        private:
            const Tokens::Token& keyword;

        public:
            explicit BaseFunctionCallNode( const Tokens::Token& keyword);

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
