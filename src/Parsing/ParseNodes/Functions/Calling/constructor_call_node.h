#ifndef CONSTRUCTOR_CALL_NODE_H
#define CONSTRUCTOR_CALL_NODE_H

#include "../../../../Lexing/Tokens/token.h"

#include "../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class ConstructorCallNode final : public NodeCollection<ParseNode>
    {
        protected:
            const ParseNode* type;

            const Tokens::Token& keyword;

        public:
            ConstructorCallNode(const ParseNode* type, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Type() const;

            [[nodiscard]] unsigned long Index() const override;

            ~ConstructorCallNode() override;
    };
}

#endif
