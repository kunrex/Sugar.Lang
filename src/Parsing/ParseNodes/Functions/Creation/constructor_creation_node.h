#ifndef CONSTRUCTOR_CREATION_NODE_H
#define CONSTRUCTOR_CREATION_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Functions::Creation
{
    class ConstructorCreationNode final : public virtual FixedNodeCollection<3>
    {
        public:
            ConstructorCreationNode(const IParseNode* describer, const IParseNode* parameters, const IParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
