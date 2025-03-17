#ifndef INDEXED_CONTEXT_H
#define INDEXED_CONTEXT_H

#include "variable_context.h"

namespace Analysis::Structure::Context
{
    class IndexedContext : public VariableContext
    {
        protected:
            const int index;

            IndexedContext(const Core::Interfaces::IVariable* variable, int index);

        public:
            [[nodiscard]] int Index() const;
    };
}

#endif
