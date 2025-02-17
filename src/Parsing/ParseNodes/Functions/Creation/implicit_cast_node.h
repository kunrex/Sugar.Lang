#ifndef IMPLICIT_CAST_NODE_H
#define IMPLICIT_CAST_NODE_H

#include "keyword_function_node.h"

namespace ParseNodes::Functions::Creation
{
    class ImplicitCastNode final : public KeywordFunctionNode
    {
        public:
            ImplicitCastNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const Groups::ScopeNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
