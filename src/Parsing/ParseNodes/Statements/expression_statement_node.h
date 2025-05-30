#ifndef EXPRESSION_STATEMENT_NODE_H
#define EXPRESSION_STATEMENT_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Statements
{
    class ExpressionStatementNode final : public virtual FixedNodeCollection<1>
    {
        public:
            ExpressionStatementNode(const IParseNode* expression, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
