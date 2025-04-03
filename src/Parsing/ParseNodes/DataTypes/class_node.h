#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include "data_type_node.h"

namespace ParseNodes::DataTypes
{
    class ClassNode final : public DataTypeNode
    {
        public:
            ClassNode(const Describers::DescriberNode* describer, const Values::IdentifierNode* identifier, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
