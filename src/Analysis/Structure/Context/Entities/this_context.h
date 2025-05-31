#ifndef THIS_CONTEXT_H
#define THIS_CONTEXT_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class ThisContext final : public ContextNode
    {
        public:
            explicit ThisContext(const Core::Interfaces::IDataType* creationType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
