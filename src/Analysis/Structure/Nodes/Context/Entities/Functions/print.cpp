#include "print.h"

namespace Analysis::Structure::Context
{
    Print::Print() : ContextNode(nullptr), Collection()
    { }

    bool Print::Readable() const { return false; }
    bool Print::Writable() const { return false; }

    std::string Print::InstructionGet() const { return "call void [mscorlib]System.Console::Write"; }
    std::string Print::InstructionSet() const { return ""; }

    int Print::SlotCount() const
    {
        int maxCount = 1;

        for (const auto child: children)
        {
            if (const auto c = 2 + child->SlotCount(); c > maxCount)
                maxCount = c;
        }

        return maxCount == 1 ? 0 : maxCount;
    }
}
