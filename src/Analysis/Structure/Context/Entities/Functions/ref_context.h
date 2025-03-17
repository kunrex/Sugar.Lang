#ifndef REF_CONTEXT_H
#define REF_CONTEXT_H

#include "../../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class RefContext final : public UnaryContextNode
    {
        private:
            mutable int slotCount;

        public:
            explicit RefContext(const ContextNode* context);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}


#endif
