#ifndef ENUM_NODE_H
#define ENUM_NODE_H

#include "data_type_node.h"

namespace ParseNodes::DataTypes
{
    class EnumNode final : public DataTypeNode
    {
        public:
            EnumNode(const Describers::DescriberNode* describer, const Values::IdentifierNode* identifier, const NodeCollection<ParseNode>* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif //ENUM_NODE_H
