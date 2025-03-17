#ifndef THROW_CONTEXT_H
#define THROW_CONTEXT_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class ThrowContext final : public ContextNode
    {
        public:
            ThrowContext();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
