#ifndef UNBOX_INSTRUCTION_H
#define UNBOX_INSTRUCTION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Structure
{
    class UnBoxInstruction final : public Context::UnaryContextNode
    {
        public:
            explicit UnBoxInstruction(const Core::DataType* creationType, const ContextNode* operand);

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
