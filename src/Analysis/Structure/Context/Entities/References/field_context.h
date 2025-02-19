#ifndef FIELD_CONTEXT_H
#define FIELD_CONTEXT_H

#include "../variable_context.h"

namespace Analysis::Structure::Context
{
    class FieldContext final : public VariableContext
    {
        private:
            mutable std::string getInstruction;
            mutable std::string setInstruction;

        public:
            explicit FieldContext(const Core::Characteristic* characteristic);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
