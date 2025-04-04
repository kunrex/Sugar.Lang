#include "function_extensions.h"

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace ParseNodes::Enums;

namespace Analysis::Structure::Context
{
    int CalculateFunctionCallSlotSize(const BinaryContextNode* binaryContext)
    {
        int slotCount = 0, argCount = 0;
        const auto lhs = binaryContext->GetChild(static_cast<int>(ChildCode::LHS)), rhs = binaryContext->GetChild(static_cast<int>(ChildCode::LHS));

        if (const auto size = lhs->SlotCount(); size > slotCount - argCount)
            slotCount = size + argCount;

        const auto value = lhs->CreationType()->SlotCount();
        argCount += value;
        slotCount += value;

        if (const auto size = rhs->SlotCount(); size > slotCount - argCount)
            slotCount = size + argCount;

        return slotCount + rhs->CreationType()->SlotCount();
    }

    int CalculateFunctionCallSlotSize(const DynamicContextCollection* const function)
    {
        int slotCount = 0, argCount = 0;

        for (auto i = 0; i < function->ChildCount(); i++)
        {
            const auto child = function->GetChild(i);
            if (const auto size = child->SlotCount(); size > slotCount - argCount)
                slotCount = size + argCount;

            const auto value = child->CreationType()->SlotCount();
            argCount += value;
            slotCount += value;
        }

        return slotCount;
    }
}
