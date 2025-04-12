#ifndef ACTION_TYPE_H
#define ACTION_TYPE_H

#include "../../../parse_node.h"

namespace ParseNodes::Types
{
    class ActionTypeNode final : public DynamicNodeCollection
    {
        public:
            explicit ActionTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
