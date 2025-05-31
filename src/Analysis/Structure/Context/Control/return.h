#ifndef RETURN_H
#define RETURN_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class Return final : public ContextNode
    {
        public:
            Return();
            explicit Return(const Core::Interfaces::IDataType* dataType);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
