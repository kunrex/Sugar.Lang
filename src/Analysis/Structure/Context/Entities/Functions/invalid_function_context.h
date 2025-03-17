#ifndef INVALID_FUNCTION_CONTEXT_H
#define INVALID_FUNCTION_CONTEXT_H

#include "../../context_node.h"
#include "../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class InvalidFunctionContext final : public ContextNode, public Services::ConstantCollection<ContextNode>
    {
        public:
            InvalidFunctionContext();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
