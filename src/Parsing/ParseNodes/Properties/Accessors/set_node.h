#ifndef SET_NODE_H
#define SET_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Properties
{
    class SetNode final : public virtual FixedNodeCollection<2>
    {
        public:
            SetNode(const IParseNode* describer, const IParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
