#include "branch_condition.h"

#include <format>

#include "../../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    BranchTrue::BranchTrue(const std::string& name) : ContextNode(&Object::Instance()), cilInstruction(std::format("brtrue {}", name))
    { }

    MemberType BranchTrue::MemberType() const { return MemberType::BranchJump; }

    bool BranchTrue::Readable() const { return false; }
    bool BranchTrue::Writable() const { return false; }

    std::string BranchTrue::InstructionGet() const { return cilInstruction; }
    std::string BranchTrue::InstructionSet() const { return ""; }

    BranchFalse::BranchFalse(const std::string& name) : ContextNode(&Object::Instance()), cilInstruction(std::format("brfalse {}", name))
    { }

    MemberType BranchFalse::MemberType() const { return MemberType::BranchJump; }

    bool BranchFalse::Readable() const { return false; }
    bool BranchFalse::Writable() const { return false; }

    std::string BranchFalse::InstructionGet() const { return cilInstruction; }
    std::string BranchFalse::InstructionSet() const { return ""; }
}

