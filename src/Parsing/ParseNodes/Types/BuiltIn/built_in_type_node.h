#ifndef BUILT_IN_TYPE_H
#define BUILT_IN_TYPE_H

#include "../../parse_node.h"

namespace ParseNodes::Types
{
    class BuiltInTypeNode final : public ParseNode
    {
        public:
            explicit BuiltInTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif