#ifndef LIST_TYPE_NODE_H
#define LIST_TYPE_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Types
{
    class ListTypeNode final : public DynamicNodeCollection
    {
        public:
            explicit ListTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
