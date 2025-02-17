#include "static_reference_context.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    StaticReferenceContext::StaticReferenceContext(const DataType* creationType) : ContextNode(creationType)
    { }

    MemberType StaticReferenceContext::MemberType() const { return MemberType::StaticReferenceContext; }

    bool StaticReferenceContext::Readable() const { return true; }
    bool StaticReferenceContext::Writable() const { return false; }

    std::string StaticReferenceContext::InstructionGet() const { return ""; }
    std::string StaticReferenceContext::InstructionSet() const { return ""; }

    int StaticReferenceContext::SlotCount() const { return 0; }
}