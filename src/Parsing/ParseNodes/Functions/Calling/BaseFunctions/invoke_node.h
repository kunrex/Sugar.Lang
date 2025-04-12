#ifndef INVOKE_NODE_H
#define INVOKE_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class InvokeNode final : public DynamicNodeCollection
    {
        public:
            explicit InvokeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
