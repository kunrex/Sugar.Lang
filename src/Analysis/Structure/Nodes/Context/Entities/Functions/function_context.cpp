#include "function_context.h"

#include "../../../../Core/DataTypes/data_type.h"

#include <format>
#include <functional>

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    FunctionContext::FunctionContext(const FunctionDefinition* function, bool isStatic) : ContextNode(function->CreationType()), cilInstruction(std::format("call {} {}", isStatic ? "" : "instance", function->SignatureString())), slotCount(-1), function(function)
    { }

    MemberType FunctionContext::MemberType() const { return MemberType::FunctionCallContext; }

    bool FunctionContext::Readable() const { return true; }
    bool FunctionContext::Writable() const { return function->Writable(); }

    std::string FunctionContext::InstructionGet() const { return cilInstruction; }
    std::string FunctionContext::InstructionSet() const { return ""; }

    int FunctionContext::SlotCount() const
    {
        if (slotCount == -1)
        {
            slotCount = 0;

            int argCount = 0;
            for (const auto child: children)
            {
                if (const auto size = child->SlotCount(); size > slotCount - argCount)
                    slotCount = size + argCount;

                argCount += child->CreationType()->SlotCount();
                slotCount += child->CreationType()->SlotCount();
            }

            slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }
}

