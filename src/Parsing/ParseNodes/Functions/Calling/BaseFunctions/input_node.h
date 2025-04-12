#ifndef INPUT_NODE_H
#define INPUT_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class InputNode final : public DynamicNodeCollection
    {
        public:
            explicit InputNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
