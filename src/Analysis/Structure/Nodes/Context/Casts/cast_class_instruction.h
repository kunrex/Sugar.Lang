#ifndef CAST_INSTRUCTION_H
#define CAST_INSTRUCTION_H

#include "../unary_context_node.h"
#include "../../../Core/Context/built_in_instruction.h"

namespace Analysis::Structure::Context
{
    class CastClassInstruction final : public UnaryContextNode
    {
        public:
            explicit CastClassInstruction(const Core::DataType* creationType, const ContextNode* operand);

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
