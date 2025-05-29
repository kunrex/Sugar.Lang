#include "branch_condition.h"

#include <format>

#include "../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    BranchTrue::BranchTrue(const string& name) : ContextNode(Object::Instance()), cilInstruction(std::format("brtrue {}", name))
    { }

    MemberType BranchTrue::MemberType() const { return MemberType::BranchJump; }

    int BranchTrue::SlotCount() const { return 0; }

    bool BranchTrue::Readable() const { return false; }
    bool BranchTrue::Writable() const { return false; }

    string BranchTrue::CILData() const { return cilInstruction; }

    BranchFalse::BranchFalse(const string& name) : ContextNode(Object::Instance()), cilInstruction(std::format("brfalse {}", name))
    { }

    MemberType BranchFalse::MemberType() const { return MemberType::BranchJump; }

    int BranchFalse::SlotCount() const { return 0; }

    bool BranchFalse::Readable() const { return false; }
    bool BranchFalse::Writable() const { return false; }

    string BranchFalse::CILData() const { return cilInstruction; }
}

