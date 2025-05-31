#ifndef INPUT_CONTEXT_H
#define INPUT_CONTEXT_H

#include "../../context_node.h"

namespace Analysis::Structure::Context
{
    class InputContext final : public ContextNode
    {
        public:
            InputContext();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
