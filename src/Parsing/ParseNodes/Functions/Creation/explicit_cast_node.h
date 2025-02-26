#ifndef EXPLICIT_CAST_NODE_H
#define EXPLICIT_CAST_NODE_H

#include "keyword_function_node.h"

namespace ParseNodes::Functions::Creation
{
    class ExplicitCastNode final : public KeywordFunctionNode
    {
        public:
            ExplicitCastNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const NodeCollection<ParseNode>* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
