#include "local_variable_address_context.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    LocalVariableAddressContext::LocalVariableAddressContext(const IVariable* const variable, const int index) : IndexedContext(variable, true, index)
    { }

    MemberType LocalVariableAddressContext::MemberType() const { return MemberType::LocalVariableContext; }

    int LocalVariableAddressContext::SlotCount() const { return 1; }

    bool LocalVariableAddressContext::Writable() const { return false; }

    string LocalVariableAddressContext::CILInstruction() const
    {
        return "ldloca." + index;
    }
}