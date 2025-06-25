#ifndef ENUM_NODE_H
#define ENUM_NODE_H

#include "../parse_node.h"

namespace ParseNodes::DataTypes
{
    class EnumNode final : public virtual FixedNodeCollection<3>
    {
        public:
            EnumNode(const IParseNode* describer, const IParseNode* identifier, const IParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
