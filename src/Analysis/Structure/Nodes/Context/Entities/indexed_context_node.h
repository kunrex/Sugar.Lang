#ifndef INDEXED_CONTEXT_NODE_H
#define INDEXED_CONTEXT_NODE_H

#include "variable_context.h"

namespace Analysis::Structure::Context
{
    class IndexedContextNode : public VariableContext
    {
        protected:
            const int index;

            IndexedContextNode(const Core::Characteristic* characteristic, int index);

        public:
            [[nodiscard]] int Index() const;
    };
}

#endif
