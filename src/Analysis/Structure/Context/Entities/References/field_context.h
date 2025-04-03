#ifndef FIELD_CONTEXT_H
#define FIELD_CONTEXT_H

#include "../variable_context.h"

namespace Analysis::Structure::Context
{
    class FieldContext final : public VariableContext
    {
        private:
            const bool writable;

        public:
            FieldContext(const Core::Interfaces::IVariable* variable, bool bypassWrite);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Writable() const override;
    };
}

#endif
