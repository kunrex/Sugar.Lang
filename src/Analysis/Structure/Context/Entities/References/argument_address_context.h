#ifndef ARGUMENT_ADDRESS_CONTEXT_H
#define ARGUMENT_ADDRESS_CONTEXT_H

#include "../indexed_context.h"

namespace Analysis::Structure::Context
{
    class ArgumentAddressContext final : public IndexedContext
    {
        public:
            ArgumentAddressContext(const Core::Interfaces::IVariable* variable, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
