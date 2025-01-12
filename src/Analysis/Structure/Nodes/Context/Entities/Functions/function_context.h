#ifndef FUNCTION_CONTEXT_H
#define FUNCTION_CONTEXT_H

#include "../../context_node.h"
#include "../../../Creation/Functions/function_definition.h"

namespace Analysis::Structure::Context
{
    class FunctionContext final : public ContextNode, public Services::Collection<ContextNode>
    {
        protected:
            const Creation::FunctionDefinition* function;

            explicit FunctionContext(const Creation::FunctionDefinition* function);

        public:
            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] bool IsStatic() const;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
