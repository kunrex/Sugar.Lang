#ifndef FIELD_ADDRESS_CONTEXT_H
#define FIELD_ADDRESS_CONTEXT_H

#include "../variable_context.h"

namespace Analysis::Structure::Context
{
    class FieldAddressContext final : public VariableContext
    {
        public:
            explicit FieldAddressContext(const Core::Interfaces::IVariable* variable);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
