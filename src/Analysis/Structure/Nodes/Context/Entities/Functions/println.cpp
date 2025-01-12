#include "println.h"

namespace Analysis::Structure::Context
{
    Println::Println() : ContextNode(nullptr), Collection()
    { }

    bool Println::Readable() const { return false; }
    bool Println::Writable() const { return false; }

    std::string Println::InstructionGet() const { return "call void [mscorlib]System.Console::WriteLine"; }
    std::string Println::InstructionSet() const { return ""; }

    int Println::SlotCount() const
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

