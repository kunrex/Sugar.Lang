#ifndef FIELD_CONTEXT_H
#define FIELD_CONTEXT_H

#include "../../../Core/Interfaces/Creation/i_characteristic.h"

namespace Analysis::Structure::Context
{
    class FieldContext final : public ContextNode
    {
        private:
            const bool writable;
            const Core::Interfaces::ICharacteristic* characteristic;

        public:
            FieldContext(const Core::Interfaces::ICharacteristic* characteristic, bool bypassWrite);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] uintptr_t Metadata() const override;
            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
