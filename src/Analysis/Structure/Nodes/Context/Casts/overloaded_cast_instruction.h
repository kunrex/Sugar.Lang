#ifndef OVERLOADED_CAST_INSTRUCTION_H
#define OVERLOADED_CAST_INSTRUCTION_H

#include "../unary_context_node.h"
#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Context
{
    class OverloadedCastInstruction : public UnaryContextNode
    {
        private:
            const Creation::CastDefinition* definition;

        public:
            explicit OverloadedCastInstruction(const Creation::CastDefinition* definition, const ContextNode* operand);

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
