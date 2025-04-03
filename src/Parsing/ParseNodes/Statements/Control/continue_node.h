#ifndef CONTINUE_NODE_H
#define CONTINUE_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Statements
{
    class ContinueNode final : public ParseNode
    {
        public:
            explicit ContinueNode(const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
