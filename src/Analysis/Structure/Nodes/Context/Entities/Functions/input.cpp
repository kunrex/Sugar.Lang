#include "input.h"

#include "../../../../Wrappers/Reference/string.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    Input::Input() : ContextNode(&String::Instance())
    {
        slotCount = creationType->SlotCount();
    }

    MemberType Input::MemberType() const { return MemberType::InputContext; }

    bool Input::Readable() const { return true; }
    bool Input::Writable() const { return false; }

    std::string Input::InstructionGet() const { return "call string [mscorlib]System.Console::ReadLine()"; }
    std::string Input::InstructionSet() const { return ""; }
}

