#ifndef FUNCTION_CREATION_NODE_H
#define FUNCTION_CREATION_NODE_H

#include "../../parse_node.h"
#include "../../Core/function_node.h"

namespace ParseNodes::Functions::Creation
{
    class FunctionCreationNode final : public ParseNode, public Core::FunctionNode, public Core::NameableNode
    {
        public:
            FunctionCreationNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier, const Groups::CompoundDeclarationNode* parameters, const NodeCollection<ParseNode>* body);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
