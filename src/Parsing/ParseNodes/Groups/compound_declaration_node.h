#ifndef COMPOUND_DECLARATION_NODE_H
#define COMPOUND_DECLARATION_NODE_H

#include "../parse_node.h"
#include "../Statements/declaration_node.h"

namespace ParseNodes::Groups
{
    class CompoundDeclarationNode final : public NodeCollection<Statements::DeclarationNode>
    {
        public:
            CompoundDeclarationNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
