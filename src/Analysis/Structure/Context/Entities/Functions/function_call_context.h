#ifndef FUNCTION_CALL_CONTEXT_H
#define FUNCTION_CALL_CONTEXT_H

#include "../../context_node.h"
#include "../../../Creation/Functions/function_definition.h"

namespace Analysis::Structure::Context
{
    class FunctionCallContext final : public ContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            mutable int slotCount;
            const Creation::FunctionDefinition* function;

        public:
            explicit FunctionCallContext(const Creation::FunctionDefinition* function);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
