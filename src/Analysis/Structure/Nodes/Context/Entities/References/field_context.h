#ifndef FIELD_CONTEXT_H
#define FIELD_CONTEXT_H

#include "../variable_context.h"

namespace Analysis::Structure::Context
{
    class FieldContext final : public VariableContext
    {
        public:
            explicit FieldContext(const Creation::Variable* variable);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
