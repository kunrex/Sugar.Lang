#ifndef BASE_PROPERTY_NODE_H
#define BASE_PROPERTY_NODE_H

#include "Accessors/get_node.h"
#include "Accessors/set_node.h"

#include "../parse_node.h"
#include "../Values/identifier_node.h"
#include "../Describers/describer_node.h"

namespace ParseNodes::Properties
{
    class BasePropertyNode final : public virtual FixedNodeCollection<5>
    {
        public:
            BasePropertyNode(const Describers::DescriberNode* describer, const IParseNode* type, const Values::IdentifierNode* identifier, const GetNode* get, const SetNode* set);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
