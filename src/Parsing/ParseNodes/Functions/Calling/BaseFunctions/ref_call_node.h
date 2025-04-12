#ifndef REF_CALL_NODE_H
#define REF_CALL_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class RefCallNode final : public DynamicNodeCollection
    {
        public:
            explicit RefCallNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
