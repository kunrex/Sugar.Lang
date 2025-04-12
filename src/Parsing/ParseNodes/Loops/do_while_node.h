#ifndef DO_WHILE_NODE_H
#define DO_WHILE_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Loops
{
    class DoWhileNode final : public virtual FixedNodeCollection<2>
    {
        public:
            DoWhileNode(const IParseNode* condition, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
