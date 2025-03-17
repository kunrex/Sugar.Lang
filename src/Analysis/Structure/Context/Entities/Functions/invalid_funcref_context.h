#ifndef INVALID_FUNCREF_CONTEXT_H
#define INVALID_FUNCREF_CONTEXT_H

#include "../../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class InvalidFuncRefContext final : public UnaryContextNode
    {
        public:
            explicit InvalidFuncRefContext(const ContextNode* objectContext);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
