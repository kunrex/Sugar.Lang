#ifndef INDEXED_CONTEXT_NODE_H
#define INDEXED_CONTEXT_NODE_H

#include "variable_context.h"

namespace Analysis::Structure::Context
{
    class IndexedContextNode : public VariableContext
    {
        protected:
            int index;

            IndexedContextNode(const Creation::Variable* variable, int index);

        public:
            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] int Index() const;
    };
}

#endif
