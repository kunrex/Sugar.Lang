#ifndef FIELD_CONTEXT_H
#define FIELD_CONTEXT_H

#include "../variable_context.h"

namespace Analysis::Structure::Context
{
    class FieldContext final : public VariableContext
    {
        public:
            FieldContext(const Core::Interfaces::IVariable* variable, bool isLoadInstruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
