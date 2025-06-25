#include "format_context.h"

#include "function_extensions.h"

#include "../../../Wrappers/Reference/string.h"

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    FormatContext::FormatContext() : DynamicContextCollection(String::Instance()), slotCount(-1)
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

    std::string FormatContext::CILData() const { return "call string [System.Runtime]System.String::Format(string, object[])"; }

    void FormatContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Format" << std::endl;
        DynamicContextCollection::Print(indent, last);
    }

    FormatSingleContext::FormatSingleContext(const IContextNode* const arg, const IContextNode* const operand) : BinaryContextNode(String::Instance(), arg, operand), slotCount(-1)
    { }

    int FormatSingleContext::SlotCount() const
    {
        if (slotCount < 0)
            slotCount = CalculateFunctionCallSlotSize(this);

        return slotCount;
    }

    MemberType FormatSingleContext::MemberType() const { return MemberType::FormatSingleContext; }

    bool FormatSingleContext::Readable() const { return true; }
    bool FormatSingleContext::Writable() const { return false; }

    std::string FormatSingleContext::CILData() const { return "call string [System.Runtime]System.String::Format(string, object)"; }

    void FormatSingleContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Format Single" << std::endl;
        FixedContextCollection::Print(indent, last);
    }

    FormatDoubleContext::FormatDoubleContext(const IContextNode* const arg, const IContextNode* const arg1, const IContextNode* const arg2) : FixedContextCollection<3>(String::Instance()), slotCount(-1)
    {
        AddChild(ChildCode::Expression, arg);
        AddChild(ChildCode::LHS, arg1);
        AddChild(ChildCode::RHS, arg2);
    }

    int FormatDoubleContext::SlotCount() const
    {
        if (slotCount < 0)
        {
            slotCount = 0;
            int argCount = 0;
            const auto arg = GetChild(static_cast<int>(ChildCode::Expression)), lhs = GetChild(static_cast<int>(ChildCode::LHS)), rhs = GetChild(static_cast<int>(ChildCode::LHS));

            if (const auto size = arg->SlotCount(); size > slotCount - argCount)
                slotCount = size + argCount;

            auto value = arg->CreationType()->SlotCount();
            argCount += value;
            slotCount += value;

            if (const auto size = lhs->SlotCount(); size > slotCount - argCount)
                slotCount = size + argCount;

            value = lhs->CreationType()->SlotCount();
            argCount += value;
            slotCount += value;

            if (const auto size = rhs->SlotCount(); size > slotCount - argCount)
                slotCount = size + argCount;

            slotCount += rhs->CreationType()->SlotCount();
        }

        return slotCount;
    }

    MemberType FormatDoubleContext::MemberType() const { return MemberType::FormatDoubleContext; }

    bool FormatDoubleContext::Readable() const { return true; }
    bool FormatDoubleContext::Writable() const { return false; }

    std::string FormatDoubleContext::CILData() const { return "call string [System.Runtime]System.String::Format(string, object, object)"; }

    void FormatDoubleContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Format Double" << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}
