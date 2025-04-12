#ifndef FORMAT_NODE_H
#define FORMAT_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class FormatNode final : public DynamicNodeCollection
    {
        public:
            explicit FormatNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
