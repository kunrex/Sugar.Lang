#ifndef INVALID_NODE_H
#define INVALID_NODE_H

#include "parse_node.h"

namespace ParseNodes
{
    class InvalidNode final : public DynamicNodeCollection
    {
        public:
            explicit InvalidNode(const Tokens::Token& token);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif