#ifndef WHILE_NODE_H
#define WHILE_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Loops
{
    class WhileNode final : public virtual FixedNodeCollection<2>
    {
        public:
            WhileNode(const IParseNode* condition, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
