#include "input.h"

namespace Analysis::Structure::Context
{
    Input::Input() : ContextNode(Class.String)
    { }

    bool Input::Readable() const { return true; }
    bool Input::Writable() const { return false; }

    std::string Input::InstructionGet() const { return "call string [mscorlib]System.Console::ReadLine()"; }
    std::string Input::InstructionSet() const { return ""; }

    int Input::SlotCount() const
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

