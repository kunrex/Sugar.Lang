#include "branch.h"

#include <format>

#include "../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    Branch::Branch(const std::string& name) : ContextNode(Object::Instance()), cilInstruction(std::format("br {}", name))
    { }

    MemberType Branch::MemberType() const { return MemberType::BranchJump; }

    int Branch::SlotCount() const { return 0; }

    bool Branch::Readable() const { return false; }
    bool Branch::Writable() const { return false; }

    std::string Branch::CILData() const { return cilInstruction; }

    void Branch::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Branch: " << cilInstruction << std::endl;
    }

    BranchTrue::BranchTrue(const std::string& name) : ContextNode(Object::Instance()), cilInstruction(std::format("brtrue {}", name))
    { }

    MemberType BranchTrue::MemberType() const { return MemberType::BranchJump; }

    int BranchTrue::SlotCount() const { return 0; }

    bool BranchTrue::Readable() const { return false; }
    bool BranchTrue::Writable() const { return false; }

    std::string BranchTrue::CILData() const { return cilInstruction; }

    void BranchTrue::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Branch True: " << cilInstruction << std::endl;
    }

    BranchFalse::BranchFalse(const std::string& name) : ContextNode(Object::Instance()), cilInstruction(std::format("brfalse {}", name))
    { }

    MemberType BranchFalse::MemberType() const { return MemberType::BranchJump; }

    int BranchFalse::SlotCount() const { return 0; }

    bool BranchFalse::Readable() const { return false; }
    bool BranchFalse::Writable() const { return false; }

    std::string BranchFalse::CILData() const { return cilInstruction; }

    void BranchFalse::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Branch False: " << cilInstruction << std::endl;
    }
}
