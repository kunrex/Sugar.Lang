#ifndef LOCAL_VARIABLE_ADDRESS_CONTEXT_H
#define LOCAL_VARIABLE_ADDRESS_CONTEXT_H

#include "../indexed_context.h"

namespace Analysis::Structure::Context
{
    class LocalVariableAddressContext final : public IndexedContext
    {
        public:
            LocalVariableAddressContext(const Core::Interfaces::IVariable* variable, int index);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
