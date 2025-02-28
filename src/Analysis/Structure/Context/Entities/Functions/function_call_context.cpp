#include "function_call_context.h"

#include <format>

#include "function_extensions.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    FunctionCallContext::FunctionCallContext(const FunctionDefinition* const function) : ContextNode(function->CreationType()), slotCount(-1), function(function)
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
    bool FunctionCallContext::Writable() const { return function->CreationType() != nullptr; }

    string FunctionCallContext::CILInstruction() const { return "call " + function->FullName(); }
}

