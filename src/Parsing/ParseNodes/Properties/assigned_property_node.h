#ifndef ASSIGNED_PROPERTY_NODE_H
#define ASSIGNED_PROPERTY_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Properties
{
    class AssignedPropertyNode final : public virtual FixedNodeCollection<6>
    {
        public:
            AssignedPropertyNode(const IParseNode* describer, const IParseNode* type, const IParseNode* identifier, const IParseNode* get, const IParseNode* set, const IParseNode* value);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}


#endif
