#ifndef INITIALISATION_NODE_H
#define INITIALISATION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Statements
{
    class InitialisationNode final : public virtual FixedNodeCollection<4>
    {
        public:
            InitialisationNode(const IParseNode* describer, const IParseNode* type, const IParseNode* identifier, const IParseNode* value, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
