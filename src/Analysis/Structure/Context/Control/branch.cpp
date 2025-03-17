#include "branch.h"

#include <format>

#include "../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    Branch::Branch(const string& name) : ContextNode(&Object::Instance()), cilInstruction(std::format("br {}", name))
    { }

    MemberType Branch::MemberType() const { return MemberType::BranchJump; }

    int Branch::SlotCount() const { return 0; }

    bool Branch::Readable() const { return false; }
    bool Branch::Writable() const { return false; }

    string Branch::CILData() const { return cilInstruction; }
}
