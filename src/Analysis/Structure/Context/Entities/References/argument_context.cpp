#include "argument_context.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ArgumentContext::ArgumentContext(const IVariable* const variable, const bool isLoadInstruction, const int index) : IndexedContext(variable, isLoadInstruction, index)
    { }

    MemberType ArgumentContext::MemberType() const { return MemberType::FunctionArgumentContext; }

    int ArgumentContext::SlotCount() const { return creationType->SlotCount(); }

    string ArgumentContext::CILInstruction() const
    {
        if (isLoadInstruction)
            return "ldarg." + index;

        return "starg." + index;;
    }
}
