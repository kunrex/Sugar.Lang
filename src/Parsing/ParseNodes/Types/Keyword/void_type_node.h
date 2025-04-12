#ifndef VOID_TYPE_H
#define VOID_TYPE_H

#include "../../parse_node.h"

namespace ParseNodes::Types
{
    class VoidTypeNode final : public ParseNode
    {
        public:
            explicit VoidTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif