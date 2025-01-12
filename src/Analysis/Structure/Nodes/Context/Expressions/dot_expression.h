#ifndef DOT_EXPRESSION_H
#define DOT_EXPRESSION_H

#include "../binary_context_node.h"

namespace Analysis::Structure::Context
{
    class DotExpression final : public BinaryContextNode
    {
        public:
            DotExpression(const ContextNode* lhs, const ContextNode* rhs);

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
