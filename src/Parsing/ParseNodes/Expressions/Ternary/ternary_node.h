#ifndef TERNARY_NODE_H
#define TERNARY_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Expressions
{
    class TernaryNode final : public FixedNodeCollection<3>
    {
        public:
            TernaryNode(const IParseNode* condition, const IParseNode* trueValue, const IParseNode* falseValue, const Tokens::Token& questionMark);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
