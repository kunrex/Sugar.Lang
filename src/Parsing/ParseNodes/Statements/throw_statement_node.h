#ifndef THROW_STATEMENT_NODE_H
#define THROW_STATEMENT_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Statements
{
    class ThrowStatementNode final : public FixedNodeCollection<1>
    {
        public:
            ThrowStatementNode(const IParseNode* exception, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
