#ifndef EXPRESSION_LIST_NODE_H
#define EXPRESSION_LIST_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class ExpressionListNode final : public DynamicNodeCollection
    {
        public:
            explicit ExpressionListNode(const Tokens::Token& token);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
