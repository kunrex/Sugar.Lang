#ifndef COMPOUND_DECLARATION_NODE_H
#define COMPOUND_DECLARATION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class CompoundDeclarationNode final : public DynamicNodeCollection
    {
        public:
            CompoundDeclarationNode(const Tokens::Token& token, const IParseNode* describer, const IParseNode* type);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };

    class MultipleDeclarationNode final : public DynamicNodeCollection
    {
        public:
            explicit MultipleDeclarationNode(const Tokens::Token& token);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
