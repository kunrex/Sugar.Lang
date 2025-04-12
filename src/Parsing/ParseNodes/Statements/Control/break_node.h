#ifndef BREAK_NODE_H
#define BREAK_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Statements
{
    class BreakNode final : public ParseNode
    {
        public:
            explicit BreakNode(const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
