#ifndef BUILT_IN_CAST_INSTRUCTION_H
#define BUILT_IN_CAST_INSTRUCTION_H

#include "../unary_context_node.h"
#include "../../Global/BuiltIn/built_in_cast.h"

namespace Analysis::Structure::Context
{
    class BuiltInCastInstruction final : public UnaryContextNode
    {
        private:
            const Global::BuiltInCast* definition;

        public:
            explicit BuiltInCastInstruction(const Global::BuiltInCast* definition, const ContextNode* operand);

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
