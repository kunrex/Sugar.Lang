#ifndef THROW_STATEMENT_NODE_H
#define THROW_STATEMENT_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Statements
{
    class ThrowStatementNode final : public FixedNodeCollection<1>
    {
        public:
            ThrowStatementNode(const ParseNode* exception, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
