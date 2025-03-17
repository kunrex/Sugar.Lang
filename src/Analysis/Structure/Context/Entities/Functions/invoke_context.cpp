#include "invoke_context.h"

#include <format>

#include "function_extensions.h"

#include "../../../Global/Variables/global_variable.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    InvokeContext::InvokeContext(const IDataType* const creationType, const GenericType* const delegateType) : ContextNode(creationType), slotCount(-1), delegateType(delegateType)
    { }

    int InvokeContext::SlotCount() const
    {
        if (slotCount < 0)
        {
            slotCount = CalculateFunctionCallSlotSize(this);

            if (creationType != nullptr)
                slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }

    MemberType InvokeContext::MemberType() const { return MemberType::FunctionCallContext; }

    bool InvokeContext::Readable() const { return true; }
    bool InvokeContext::Writable() const { return creationType != nullptr; }

    string InvokeContext::CILData() const
    {
        string parameterString;
        for (auto i = 1; i < children.size(); i++)
        {
            const auto current = children.at(i)->CreationType();
            parameterString += current->FullName();

            if (i < children.size() - 1)
                parameterString += ", ";
        }

        return std::format("callvirt instance void {}::Invoke({})", delegateType->GenericSignature(), parameterString);
    }
}
