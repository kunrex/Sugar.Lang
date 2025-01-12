#ifndef IDENTIFIER_NODE_H
#define IDENTIFIER_NODE_H

#include "value_node.h"

namespace ParseNodes::Values
{
    class IdentifierNode final : public ValueNode
    {
        public:
            explicit IdentifierNode(const Tokens::Token& identifier);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] std::string Value() const;
    };
}

#endif
