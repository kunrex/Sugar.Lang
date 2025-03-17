#ifndef I_SLOT_SIZE_H
#define I_SLOT_SIZE_H

namespace Analysis::Structure::Core::Interfaces
{
    class ISlotCount
    {
        public:
            [[nodiscard]] virtual int SlotCount() const = 0;

            virtual ~ISlotCount() = default;
    };
}

#endif
