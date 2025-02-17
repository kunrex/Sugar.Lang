#ifndef CONSTRUCTOR_CREATION_NODE_H
#define CONSTRUCTOR_CREATION_NODE_H

#include "keyword_function_node.h"

namespace ParseNodes::Functions::Creation
{
    class ConstructorCreationNode final : public KeywordFunctionNode
    {
        public:
            ConstructorCreationNode(const Describers::DescriberNode* describer, const Groups::CompoundDeclarationNode* parameters, const Groups::ScopeNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
