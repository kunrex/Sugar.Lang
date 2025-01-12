#ifndef SCOPE_NODE_H
#define SCOPE_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class ScopeNode final : public NodeCollection<ParseNode>
    {
        public:
            ScopeNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
