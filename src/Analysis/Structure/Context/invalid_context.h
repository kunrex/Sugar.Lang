#ifndef INVALID_CONTEXT_H
#define INVALID_CONTEXT_H

#include "context_node.h"

namespace Analysis::Structure::Context
{
    class InvalidContext final : public ContextNode
    {
        public:
            InvalidContext();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
