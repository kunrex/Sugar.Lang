#ifndef TOSTRING_NODE_H
#define TOSTRING_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class ToStringNode final : public DynamicNodeCollection
    {
        public:
            explicit ToStringNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
