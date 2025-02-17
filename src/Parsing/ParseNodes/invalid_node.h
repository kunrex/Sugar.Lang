#ifndef INVALID_NODE_H
#define INVALID_NODE_H

#include "parse_node.h"

namespace ParseNodes
{
    class InvalidNode final : public NodeCollection<ParseNode>
    {
        private:
            const unsigned long index;

        public:
            explicit InvalidNode(unsigned long index);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
