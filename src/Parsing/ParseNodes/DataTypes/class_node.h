#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include "../parse_node.h"
#include "../Values/identifier_node.h"
#include "../Describers/describer_node.h"

namespace ParseNodes::DataTypes
{
    class ClassNode final : public virtual FixedNodeCollection<3>
    {
        public:
            ClassNode(const Describers::DescriberNode* describer, const Values::IdentifierNode* identifier, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
