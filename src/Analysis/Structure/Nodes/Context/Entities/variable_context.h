#ifndef VARIABLE_CONTEXT_H
#define VARIABLE_CONTEXT_H

#include "../context_node.h"
#include "../../Creation/Variables/variable.h"

namespace Analysis::Structure::Context
{
    class VariableContext : public ContextNode
    {
        protected:
            const Creation::Variable* variable;

            explicit VariableContext(const Creation::Variable* variable);
    };
}

#endif
