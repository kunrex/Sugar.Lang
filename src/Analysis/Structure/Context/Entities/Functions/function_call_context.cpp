#include "function_call_context.h"

#include <format>

#include "function_extensions.h"

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    FunctionCallContext::FunctionCallContext(const IFunction* const function) : DynamicContextCollection(function->CreationType()), slotCount(-1), function(function)
    { }

    int FunctionCallContext::SlotCount() const
    {
        if (slotCount < 0)
        {
            slotCount = CalculateFunctionCallSlotSize(this);

            if (creationType != nullptr)
                slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }

    MemberType FunctionCallContext::MemberType() const { return MemberType::FunctionCallContext; }

    bool FunctionCallContext::Readable() const { return true; }
    bool FunctionCallContext::Writable() const { return function->CreationType() != nullptr && function->CreationType()->MemberType() == MemberType::Class; }

    uintptr_t FunctionCallContext::Metadata() const { return reinterpret_cast<uintptr_t>(function); }
    std::string FunctionCallContext::CILData() const { return function->FullName(); }

    void FunctionCallContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Function Call" << std::endl;
        DynamicContextCollection::Print(indent, last);
    }
}

