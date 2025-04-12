#ifndef PRINT_NODE_H
#define PRINT_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class PrintNode final : public DynamicNodeCollection
    {
        public:
            explicit PrintNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class PrintlnNode final : public DynamicNodeCollection
    {
        public:
            explicit PrintlnNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
