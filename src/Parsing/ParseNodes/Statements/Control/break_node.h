#ifndef BREAK_NODE_H
#define BREAK_NODE_H

#include "../statement_node.h"

namespace ParseNodes::Statements
{
    class BreakNode final : public StatementNode
    {
        public:
            explicit BreakNode(const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
