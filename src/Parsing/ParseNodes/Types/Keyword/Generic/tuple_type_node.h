#ifndef TUPLE_TYPE_NODE_H
#define TUPLE_TYPE_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Types
{
    class TupleTypeNode final : public DynamicNodeCollection
    {
        public:
            explicit TupleTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
