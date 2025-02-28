#ifndef VARIABLE_CONTEXT_H
#define VARIABLE_CONTEXT_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class VariableContext : public ContextNode
    {
        protected:
            const bool isLoadInstruction;
            const Core::Interfaces::IVariable* variable;

            explicit VariableContext(const Core::Interfaces::IVariable* variable, bool isLoadInstruction);

        public:
            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
