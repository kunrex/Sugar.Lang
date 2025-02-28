#include "input_context.h"

#include "../../../Wrappers/Reference/string.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    InputContext::InputContext() : ContextNode(&String::Instance())
    { }

    MemberType InputContext::MemberType() const { return MemberType::InputContext; }

    int InputContext::SlotCount() const { return String::Instance().SlotCount(); }

    bool InputContext::Readable() const { return true; }
    bool InputContext::Writable() const { return false; }

    string InputContext::CILInstruction() const { return "call string [System.Runtime]System.Console::ReadLine()"; }
}

