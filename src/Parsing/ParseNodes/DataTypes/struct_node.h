#ifndef STRUCT_NODE_H
#define STRUCT_NODE_H

#include "../parse_node.h"
#include "../Values/identifier_node.h"
#include "../Describers/describer_node.h"

namespace ParseNodes::DataTypes
{
    class StructNode final : public virtual FixedNodeCollection<3>
    {
        public:
            StructNode(const Describers::DescriberNode* describer, const Values::IdentifierNode* identifier, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
