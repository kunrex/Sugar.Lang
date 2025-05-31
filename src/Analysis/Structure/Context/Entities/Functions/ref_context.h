#ifndef REF_CONTEXT_H
#define REF_CONTEXT_H

#include "../../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class RefContext final : public UnaryContextNode
    {
        private:
            const int slotCount;

        public:
            explicit RefContext(const IContextNode* context);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}


#endif
