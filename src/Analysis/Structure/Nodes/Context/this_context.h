#ifndef THIS_CONTEXT_H
#define THIS_CONTEXT_H

#include "context_node.h"

namespace Analysis::Structure::Context
{
    class ThisContext final : public ContextNode
    {
        public:
            explicit ThisContext(const Core::DataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
