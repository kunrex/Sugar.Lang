#include "format_context.h"

#include "function_extensions.h"

#include "../../../Wrappers/Reference/string.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    FormatContext::FormatContext() : ContextNode(&String::Instance()), ConstantCollection(), slotCount(-1)
    { }

    int FormatContext::SlotCount() const
    {
        if (slotCount < 0)
            slotCount = std::max(creationType->SlotCount(), CalculateFunctionCallSlotSize(this));

        return slotCount;
    }

    MemberType FormatContext::MemberType() const { return MemberType::FormatContext; }

    bool FormatContext::Readable() const { return true; }
    bool FormatContext::Writable() const { return false; }

    string FormatContext::CILData() const { return "call string [System.Runtime]System.String::Format(string, object[])"; }

    FormatSingleContext::FormatSingleContext(const ContextNode* const operand) : UnaryContextNode(&String::Instance(), operand), slotCount(-1)
    { }

    int FormatSingleContext::SlotCount() const
    {
        if (slotCount < 0)
            slotCount = std::max(String::Instance().SlotCount(), operand->SlotCount());

        return slotCount;
    }

    MemberType FormatSingleContext::MemberType() const { return MemberType::FormatSingleContext; }

    bool FormatSingleContext::Readable() const { return true; }
    bool FormatSingleContext::Writable() const { return false; }

    string FormatSingleContext::CILData() const { return "call string [System.Runtime]System.String::Format(string, object)"; }

    FormatDoubleContext::FormatDoubleContext(const ContextNode* const arg1, const ContextNode* const arg2) : BinaryContextNode(&String::Instance(), arg1, arg2), slotCount(-1)
    { }

    int FormatDoubleContext::SlotCount() const
    {
        if (slotCount < 0)
            slotCount = std::max(creationType->SlotCount(), CalculateFunctionCallSlotSize(this));

        return slotCount;
    }

    MemberType FormatDoubleContext::MemberType() const { return MemberType::FormatDoubleContext; }

    bool FormatDoubleContext::Readable() const { return true; }
    bool FormatDoubleContext::Writable() const { return false; }

    string FormatDoubleContext::CILData() const { return "call string [System.Runtime]System.String::Format(string, object, object)"; }
}
