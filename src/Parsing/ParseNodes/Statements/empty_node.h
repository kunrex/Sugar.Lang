#ifndef EMPTY_NODE_H
#define EMPTY_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Statements
{
    class EmptyNode final : public ParseNode
    {
        public:
            explicit EmptyNode(const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
