#ifndef ARGUMENT_CONTEXT_H
#define ARGUMENT_CONTEXT_H

#include "../indexed_context.h"

namespace Analysis::Structure::Context
{
    class ArgumentContext final : public IndexedContext
    {
        public:
            ArgumentContext(const Core::Interfaces::IVariable* variable, bool isLoadInstruction, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
