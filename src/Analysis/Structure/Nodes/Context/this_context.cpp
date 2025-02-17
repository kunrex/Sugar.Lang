#include "this_context.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    ThisContext::ThisContext(const DataType* creationType) : ContextNode(creationType)
    { }

    MemberType ThisContext::MemberType() const { return MemberType::ThisContext; }

    bool ThisContext::Readable() const { return true; }
    bool ThisContext::Writable() const { return false; }

    std::string ThisContext::InstructionGet() const { return "ldarg.0"; }
    std::string ThisContext::InstructionSet() const { return ""; }
}
