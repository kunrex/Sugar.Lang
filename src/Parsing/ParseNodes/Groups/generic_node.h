#ifndef GENERIC_NODE_H
#define GENERIC_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class GenericNode final : public NodeCollection<ParseNode>
    {
        private:
            const unsigned long index;

        public:
            explicit GenericNode(unsigned long index);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
