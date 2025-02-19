#include "invalid_context.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidContext::InvalidContext() : ContextNode(nullptr)
    {
        slotCount = 0;
    }

    MemberType InvalidContext::MemberType() const { return MemberType::Invalid; }

    bool InvalidContext::Readable() const { return false; }
    bool InvalidContext::Writable() const { return false; }

    std::string InvalidContext::InstructionGet() const { return ""; }
    std::string InvalidContext::InstructionSet() const { return ""; }
}
