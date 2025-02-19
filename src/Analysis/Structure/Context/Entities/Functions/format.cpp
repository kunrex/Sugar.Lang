#include "format.h"

#include "../../../../Wrappers/Reference/string.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    Format::Format() : ContextNode(&String::Instance()), Collection(), slotCount(0)
    { }

    MemberType Format::MemberType() const { return MemberType::FormatContext; }

    bool Format::Readable() const { return true; }
    bool Format::Writable() const { return false; }

    std::string Format::InstructionGet() const { return "call string [mscorlib]System.String::Concat(object[])"; }
    std::string Format::InstructionSet() const { return ""; }

    int Format::SlotCount() const
    {
        if (slotCount == 0)
        {
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
