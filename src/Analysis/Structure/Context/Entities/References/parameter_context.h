#ifndef PARAMETER_CONTEXT_H
#define PARAMETER_CONTEXT_H

#include "../indexed_context.h"

#include "../../../Core/Interfaces/Creation/i_variable.h"

namespace Analysis::Structure::Context
{
    class ParameterContext final : public IndexedContext
    {
        public:
            ParameterContext(const Core::Interfaces::IVariable* variable, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
