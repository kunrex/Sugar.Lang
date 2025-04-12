#ifndef ELSE_NODE_H
#define ELSE_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Conditions
{
    class ElseNode final : public virtual FixedNodeCollection<1>
    {
        public:
            ElseNode(const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
