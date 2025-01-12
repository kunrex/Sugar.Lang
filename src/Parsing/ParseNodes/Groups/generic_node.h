#ifndef GENERIC_NODE_H
#define GENERIC_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class GenericNode final : public NodeCollection<ParseNode>
    {
        public:
            GenericNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
