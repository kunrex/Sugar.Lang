#ifndef VARIABLE_CONTEXT_H
#define VARIABLE_CONTEXT_H

#include "../context_node.h"
#include "../../../Core/Creation/characteristic.h"

namespace Analysis::Structure::Context
{
    class VariableContext : public ContextNode
    {
        protected:
            const Core::Characteristic* characteristic;

            explicit VariableContext(const Core::Characteristic* characteristic);
    };
}

#endif
