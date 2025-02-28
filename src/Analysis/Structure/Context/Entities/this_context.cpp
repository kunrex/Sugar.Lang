#include "this_context.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ThisContext::ThisContext(const IDataType* creationType) : ContextNode(creationType)
    { }

    MemberType ThisContext::MemberType() const { return MemberType::ThisContext; }

    int ThisContext::SlotCount() const { return 1; }

    bool ThisContext::Readable() const { return true; }
    bool ThisContext::Writable() const { return false; }

    string ThisContext::CILInstruction() const { return "ldarg.0"; }
}
