#ifndef STATIC_REFERENCE_CONTEXT_H
#define STATIC_REFERENCE_CONTEXT_H

#include "context_node.h"

namespace Analysis::Structure::Context
{
    class StaticReferenceContext final : public ContextNode
    {
        public:
            explicit StaticReferenceContext(const Core::DataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
