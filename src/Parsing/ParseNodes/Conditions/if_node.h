#ifndef IF_NODE_H
#define IF_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Conditions
{
    class IfNode final : public FixedNodeCollection<2>
    {
        public:
            IfNode(const IParseNode* condition, const IParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
