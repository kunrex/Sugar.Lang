#include "static_reference_context.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    StaticReferenceContext::StaticReferenceContext(const IDataType* creationType) : ContextNode(creationType)
    { }

    MemberType StaticReferenceContext::MemberType() const { return MemberType::StaticReferenceContext; }

    int StaticReferenceContext::SlotCount() const { return 0; }

    bool StaticReferenceContext::Readable() const { return true; }
    bool StaticReferenceContext::Writable() const { return false; }

    string StaticReferenceContext::CILInstruction() const { return ""; }
}