#ifndef I_SLOT_SIZE_H
#define I_SLOT_SIZE_H

namespace Analysis::Structure::Core::Interfaces
{
    class ISlotSize
    {
        public:
            [[nodiscard]] virtual int SlotCount() const = 0;

            virtual ~ISlotSize() = default;
    };
}

#endif
