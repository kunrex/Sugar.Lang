#ifndef SCOPE_NODE_H
#define SCOPE_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class ScopeNode final : public DynamicNodeCollection
    {
        public:
            explicit ScopeNode(const Tokens::Token& token);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
