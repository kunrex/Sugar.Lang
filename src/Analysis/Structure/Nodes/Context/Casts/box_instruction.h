#ifndef BOX_INSTRUCTION_H
#define BOX_INSTRUCTION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Structure
{
    class BoxInstruction final : public Context::UnaryContextNode
    {
        public:
            explicit BoxInstruction(const ContextNode* operand);

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
