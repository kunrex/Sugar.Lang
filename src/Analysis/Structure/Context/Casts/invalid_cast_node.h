#ifndef INVALID_CAST_NODE_H
#define INVALID_CAST_NODE_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class InvalidCastNode final : public UnaryContextNode
    {
        public:
            explicit InvalidCastNode(const Core::DataType* creationType, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
