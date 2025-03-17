#ifndef VARIABLE_CONTEXT_H
#define VARIABLE_CONTEXT_H

#include "../context_node.h"

#include "../../Core/Interfaces/Creation/i_variable.h"

namespace Analysis::Structure::Context
{
    class VariableContext : public ContextNode
    {
        protected:
            const Core::Interfaces::IVariable* variable;

            explicit VariableContext(const Core::Interfaces::IVariable* variable);

        public:
            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            [[nodiscard]] const Core::Interfaces::IVariable* Variable() const;
    };
}

#endif
