#ifndef FOR_NODE_H
#define FOR_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Loops
{
    class ForLoopNode final : public virtual FixedNodeCollection<4>
    {
        public:
            ForLoopNode(const IParseNode* pre, const IParseNode* condition, const IParseNode* post, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
