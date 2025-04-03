#ifndef DATA_TYPE_NODE_H
#define DATA_TYPE_NODE_H

#include "../parse_node.h"
#include "../Core/body_node.h"
#include "../Core/nameable_node.h"
#include "../Core/describable_node.h"

namespace ParseNodes::DataTypes
{
    class DataTypeNode : public virtual FixedNodeCollection<3>, public Core::DescribableNode<3>, public Core::NameableNode<3>, public Core::BodyNode<3>
    {
        protected:
            DataTypeNode(const Describers::DescriberNode* describer, const Values::IdentifierNode* identifier, const DynamicNodeCollection* body, const Tokens::Token& keyword);
    };
}

#endif
