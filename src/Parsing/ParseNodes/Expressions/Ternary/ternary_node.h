#ifndef TERNARY_NODE_H
#define TERNARY_NODE_H

#include "../../parse_node.h"
#include "../../../../Lexing/Tokens/token.h"

namespace ParseNodes::Expressions
{
    class TernaryNode final : public ParseNode
    {
        private:
            const ParseNode* condition;

            const ParseNode* trueValue;
            const ParseNode* falseValue;

        public:
            TernaryNode(const ParseNode* condition, const ParseNode* trueValue, const ParseNode* falseValue);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Condition() const;

            [[nodiscard]] const ParseNode* True() const;
            [[nodiscard]] const ParseNode* False() const;

            [[nodiscard]] unsigned long Index() const override;

            ~TernaryNode() override;
    };
}

#endif
