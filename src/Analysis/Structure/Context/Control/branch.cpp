#include "branch.h"

#include <format>

#include "../../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    Branch::Branch(const std::string& name) : ContextNode(&Object::Instance()), cilInstruction(std::format("br {}", name))
    { }

    MemberType Branch::MemberType() const { return MemberType::BranchJump; }

    bool Branch::Readable() const { return false; }
    bool Branch::Writable() const { return false; }

    std::string Branch::InstructionGet() const { return cilInstruction; }
    std::string Branch::InstructionSet() const { return ""; }
}
