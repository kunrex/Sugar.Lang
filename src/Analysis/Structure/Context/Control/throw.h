#ifndef THROW_H
#define THROW_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class Throw final : public UnaryContextNode
    {
        public:
            explicit Throw(const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
