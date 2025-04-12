#ifndef RETURN_NODE_H
#define RETURN_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Statements
{
    class ReturnNode final : public FixedNodeCollection<1>
    {
        public:
            explicit ReturnNode(const Tokens::Token& separator);
            ReturnNode(const IParseNode* value, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
