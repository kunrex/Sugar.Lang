#ifndef LOCAL_VARIABLE_CONTEXT_H
#define LOCAL_VARIABLE_CONTEXT_H

#include "../indexed_context.h"

namespace Analysis::Structure::Context
{
    class LocalVariableContext final : public IndexedContext
    {
        public:
            LocalVariableContext(const Core::Interfaces::IVariable* variable, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
