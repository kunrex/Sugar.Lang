#ifndef INVALID_NODE_H
#define INVALID_NODE_H

#include "parse_node.h"

namespace ParseNodes
{
    class InvalidNode final : public NodeCollection<ParseNode>
    {
        public:
            InvalidNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
