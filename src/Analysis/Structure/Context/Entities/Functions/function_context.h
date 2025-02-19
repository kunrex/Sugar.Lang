#ifndef FUNCTION_CONTEXT_H
#define FUNCTION_CONTEXT_H

#include "../../context_node.h"
#include "../../../Creation/Functions/function_definition.h"

namespace Analysis::Structure::Context
{
    class FunctionContext final : public ContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            const std::string cilInstruction;
            mutable int slotCount;

            const Creation::FunctionDefinition* function;

        public:
            explicit FunctionContext(const Creation::FunctionDefinition* function, bool isStatic);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
