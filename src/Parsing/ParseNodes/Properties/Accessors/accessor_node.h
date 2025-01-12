#ifndef ACCESSOR_NODE_H
#define ACCESSOR_NODE_H

#include "../../parse_node.h"
#include "../../Core/body_node.h"
#include "../../Core/describable_node.h"
#include "../../../../Lexing/Tokens/token.h"

namespace ParseNodes::Properties
{
    class AccessorNode : public ParseNode, public Core::DescribableNode, public Core::BodyNode
    {
        private:
            const Tokens::Token& keyword;

        public:
            AccessorNode(const Describers::DescriberNode* describer, const ParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] const Tokens::Token& Keyword() const;
    };
}

#endif
