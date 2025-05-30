#ifndef ASSIGNED_PROPERTY_NODE_H
#define ASSIGNED_PROPERTY_NODE_H

#include "../parse_node.h"
#include "../Values/identifier_node.h"
#include "../Describers/describer_node.h"

namespace ParseNodes::Properties
{
    class AssignedPropertyNode final : public virtual FixedNodeCollection<6>
    {
        public:
            AssignedPropertyNode(const Describers::DescriberNode* describer, const IParseNode* type, const Values::IdentifierNode* identifier, const IParseNode* get, const IParseNode* set, const IParseNode* value);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}


#endif
