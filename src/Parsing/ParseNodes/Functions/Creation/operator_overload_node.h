#ifndef OPERATOR_OVERLOAD_NODE_H
#define OPERATOR_OVERLOAD_NODE_H

#include "keyword_function_node.h"

namespace ParseNodes::Functions::Creation
{
    class OperatorOverloadNode final : public KeywordFunctionNode
    {
        private:
            const Tokens::Token& base;

        public:
            OperatorOverloadNode(const Describers::DescriberNode* describer, const ParseNode* type, const Tokens::Token& base, const Groups::CompoundDeclarationNode* parameters, const Groups::ScopeNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const Tokens::Token& Operator() const;
    };
}

#endif
