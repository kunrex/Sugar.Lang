#ifndef ARRAY_TYPE_H
#define ARRAY_TYPE_H

#include "../../../parse_node.h"

namespace ParseNodes::Types
{
    class ArrayTypeNode final : public DynamicNodeCollection
    {
        public:
            explicit ArrayTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
