#ifndef IDENTIFIER_NODE_H
#define IDENTIFIER_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Values
{
    class IdentifierNode final : public ParseNode
    {
        public:
            explicit IdentifierNode(const Tokens::Token& identifier);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif