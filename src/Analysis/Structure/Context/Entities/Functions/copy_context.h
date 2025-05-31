#ifndef COPY_CONTEXT_H
#define COPY_CONTEXT_H

#include "../../unary_context_node.h"
#include "../../../Wrappers/Generic/referenced.h"

namespace Analysis::Structure::Context
{
    class CopyContext final : public UnaryContextNode
    {
        private:
            const int slotCount;
            const Core::Interfaces::IDataType* referencedType;

        public:
            CopyContext(const IContextNode* context, const Wrappers::Referenced* referenced);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
