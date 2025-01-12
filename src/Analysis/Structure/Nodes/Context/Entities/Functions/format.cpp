#include "format.h"

namespace Analysis::Structure::Context
{
    Format::Format() : ContextNode(nullptr), Collection()
    { }

    bool Format::Readable() const { return true; }
    bool Format::Writable() const { return false; }

    std::string Format::InstructionGet() const { return "call string [mscorlib]System.String::Concat(object[])"; }
    std::string Format::InstructionSet() const { return ""; }

    int Format::SlotCount() const
    {
        int maxCount = 1;

        for (const auto child: children)
        {
            if (const auto c = 2 + child->SlotCount(); c > maxCount)
                maxCount = c;
        }

        return maxCount;
    }
}
