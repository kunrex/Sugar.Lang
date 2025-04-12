#ifndef FUNCREF_NODE_H
#define FUNCREF_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class FuncRefNode final : public DynamicNodeCollection
    {
        public:
            explicit FuncRefNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
