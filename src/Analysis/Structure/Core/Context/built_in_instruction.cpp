#include "built_in_instruction.h"

using namespace std;

namespace Analysis::Structure::Core
{
    BuiltInInstruction::BuiltInInstruction(string instruction) : instruction(move(instruction))
    { }

    const string& BuiltInInstruction::Instruction() const { return instruction; }
}
