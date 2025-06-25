#ifndef BASE_PROPERTY_NODE_H
#define BASE_PROPERTY_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Properties
{
    class BasePropertyNode final : public virtual FixedNodeCollection<5>
    {
        public:
            BasePropertyNode(const IParseNode* describer, const IParseNode* type, const IParseNode* identifier, const IParseNode* get, const IParseNode* set);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
