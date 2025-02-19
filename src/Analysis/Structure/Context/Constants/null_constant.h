#ifndef NULL_CONSTANT_H
#define NULL_CONSTANT_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class NullConstant final : public ContextNode
    {
        public:
            NullConstant();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
