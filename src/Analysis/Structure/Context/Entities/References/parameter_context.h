#ifndef PARAMETER_CONTEXT_H
#define PARAMETER_CONTEXT_H

#include "local_variable_context.h"

#include "../../../Core/Interfaces/Creation/i_variable.h"

namespace Analysis::Structure::Context
{
    class ParameterContext final : public LocalVariableContext
    {
        public:
            ParameterContext(const Core::Interfaces::IVariable* variable, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
