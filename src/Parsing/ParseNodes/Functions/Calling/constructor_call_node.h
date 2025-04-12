#ifndef CONSTRUCTOR_CALL_NODE_H
#define CONSTRUCTOR_CALL_NODE_H

#include "../../../../Lexing/Tokens/token.h"

#include "../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class ConstructorCallNode final : public DynamicNodeCollection
    {
        public:
            ConstructorCallNode(const IParseNode* type, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
