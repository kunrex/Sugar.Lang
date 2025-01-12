#ifndef STRUCT_NODE_H
#define STRUCT_NODE_H

#include "data_type_node.h"

namespace ParseNodes::DataTypes
{
    class StructNode final : public DataTypeNode
    {
        public:
            StructNode(const Describers::DescriberNode* describer, const Values::IdentifierNode* identifier, const NodeCollection<ParseNode>* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
