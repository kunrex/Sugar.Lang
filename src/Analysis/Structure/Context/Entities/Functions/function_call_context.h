#ifndef FUNCTION_CALL_CONTEXT_H
#define FUNCTION_CALL_CONTEXT_H

#include "../../context_node.h"

#include "../../../Creation/Functions/function_definition.h"

namespace Analysis::Structure::Context
{
    class FunctionCallContext final : public DynamicContextCollection
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IFunction* function;

        public:
            explicit FunctionCallContext(const Core::Interfaces::IFunction* function);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] uintptr_t Metadata() const override;
            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
