#ifndef DECLARATION_NODE_H
#define DECLARATION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Statements
{
    class DeclarationNode final: public virtual FixedNodeCollection<3>
    {
        public:
            DeclarationNode(const IParseNode* describer, const IParseNode* type, const IParseNode* identifier, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
