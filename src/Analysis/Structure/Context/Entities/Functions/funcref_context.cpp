#include "funcref_context.h"

#include "function_extensions.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    FuncRefContext::FuncRefContext(const IDataType* const creationType, const ContextNode* const object, const IFunctionDefinition* const function) : UnaryContextNode(creationType, object), slotCount(-1), function(function)
    { }

    MemberType FuncRefContext::MemberType() const { return MemberType::FuncRefContext; }

    int FuncRefContext::SlotCount() const
    {
        if (slotCount < 0)
            slotCount = std::max(creationType->SlotCount(), operand->SlotCount());

        return slotCount;
    }

    bool FuncRefContext::Readable() const { return false; }
    bool FuncRefContext::Writable() const { return false; }

    string FuncRefContext::CILInstruction() const
    {
        return "ldftn " + function->Signature();
    }
}
