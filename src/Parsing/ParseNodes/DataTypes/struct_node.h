#ifndef STRUCT_NODE_H
#define STRUCT_NODE_H

#include "../parse_node.h"

namespace ParseNodes::DataTypes
{
    class StructNode final : public virtual FixedNodeCollection<3>
    {
        public:
            StructNode(const IParseNode* describer, const IParseNode* identifier, const IParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
