#ifndef KEYWORD_TYPE_NODE_H
#define KEYWORD_TYPE_NODE_H

#include "../../parse_node.h"
#include "../../../../Lexing/Tokens/token.h"

namespace ParseNodes::Types
{
    class KeywordTypeNode : public ParseNode
    {
        protected:
            const Tokens::Token& keyword;

            explicit KeywordTypeNode(const Tokens::Token& keyword);

        public:
            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
