#ifndef SCOPE_NODE_H
#define SCOPE_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class ScopeNode final : public NodeCollection<ParseNode>
    {
        private:
            const unsigned long index;

        public:
            explicit ScopeNode(unsigned long index);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
