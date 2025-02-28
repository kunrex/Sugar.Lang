#include "function_extensions.h"

namespace Analysis::Structure::Context
{
    int CalculateFunctionCallSlotSize(const BinaryContextNode* binaryContext)
    {
        int slotCount = 0, argCount = 0;
        const auto lhs = binaryContext->LHS(), rhs = binaryContext->RHS();

        if (const auto size = lhs->SlotCount(); size > slotCount - argCount)
            slotCount = size + argCount;

        const auto value = lhs->CreationType()->SlotCount();
        argCount += value;
        slotCount += value;

        if (const auto size = rhs->SlotCount(); size > slotCount - argCount)
            slotCount = size + argCount;

        return slotCount + rhs->CreationType()->SlotCount();
    }

    int CalculateFunctionCallSlotSize(const Services::ConstantCollection<ContextNode>* const function)
    {
        int slotCount = 0, argCount = 0;

        for (const auto child: *function)
        {
            if (const auto size = child->SlotCount(); size > slotCount - argCount)
                slotCount = size + argCount;

            const auto value = child->CreationType()->SlotCount();
            argCount += value;
            slotCount += value;
        }

        return slotCount;
    }
}
