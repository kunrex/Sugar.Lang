#ifndef FUNC_TYPE_H
#define FUNC_TYPE_H

#include "../../../parse_node.h"

namespace ParseNodes::Types
{
    class FuncTypeNode final : public DynamicNodeCollection
    {
        public:
            explicit FuncTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
