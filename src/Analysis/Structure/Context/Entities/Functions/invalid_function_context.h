#ifndef INVALID_FUNCTION_CONTEXT_H
#define INVALID_FUNCTION_CONTEXT_H

#include "../../context_node.h"
#include "../../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class InvalidFunctionContext final : public DynamicContextCollection
    {
        public:
            InvalidFunctionContext();

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
