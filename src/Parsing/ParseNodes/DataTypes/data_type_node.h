#ifndef DATA_TYPE_NODE_H
#define DATA_TYPE_NODE_H

#include "../parse_node.h"
#include "../Core/nameable_node.h"
#include "../Core/describable_node.h"

namespace ParseNodes::DataTypes
{
    class DataTypeNode : public ParseNode, public Core::DescribableNode, public Core::NameableNode
    {
        protected:
            const NodeCollection<ParseNode>* body;

            const Tokens::Token& keyword;

            DataTypeNode(const Describers::DescriberNode* describer, const Values::IdentifierNode* identifier, const NodeCollection<ParseNode>* body, const Tokens::Token& keyword);

        public:
            [[nodiscard]] const NodeCollection<ParseNode>* Body() const;

            [[nodiscard]] unsigned long Index() const override;

            ~DataTypeNode() override;
    };
}

#endif
