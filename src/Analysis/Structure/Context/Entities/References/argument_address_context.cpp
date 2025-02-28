#include "argument_address_context.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ArgumentAddressContext::ArgumentAddressContext(const IVariable* const variable, const int index) : IndexedContext(variable, true, index)
    { }

    MemberType ArgumentAddressContext::MemberType() const { return MemberType::FunctionArgumentAddressContext; }

    int ArgumentAddressContext::SlotCount() const { return variable->CreationType()->SlotCount(); }

    bool ArgumentAddressContext::Writable() const { return false; }

    string ArgumentAddressContext::CILInstruction() const
    {
        return "ldarga." + index;
    }
}
