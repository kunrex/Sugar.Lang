#ifndef COMPOUND_DECLARATION_NODE_H
#define COMPOUND_DECLARATION_NODE_H

#include "../parse_node.h"
#include "../Statements/declaration_node.h"

namespace ParseNodes::Groups
{
    class CompoundDeclarationNode final : public DynamicNodeCollection
    {
        public:
            explicit CompoundDeclarationNode(const Tokens::Token& token);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
