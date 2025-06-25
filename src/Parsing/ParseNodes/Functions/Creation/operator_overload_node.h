#ifndef OPERATOR_OVERLOAD_NODE_H
#define OPERATOR_OVERLOAD_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Functions::Creation
{
    class OperatorOverloadNode final : public virtual FixedNodeCollection<4>
    {
        public:
            OperatorOverloadNode(const IParseNode* describer, const IParseNode* type, const Tokens::Token& base, const IParseNode* parameters, const IParseNode* body);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
