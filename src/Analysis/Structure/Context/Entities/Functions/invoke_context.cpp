#include "invoke_context.h"

#include <format>

#include "function_extensions.h"

#include "../../../Global/Variables/global_variable.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    InvokeContext::InvokeContext(const IDataType* const creationType, const IDelegateType* const delegateType) : DynamicContextCollection(creationType), slotCount(-1), delegateType(delegateType)
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

    std::string InvokeContext::CILData() const
    {
        std::string parameterString;
        for (auto i = 1; i < children.size(); i++)
        {
            parameterString.append(children.at(i)->CreationType()->FullName());

            if (i < children.size() - 1)
                parameterString.append(", ");
        }

        return std::format("callvirt instance void {}::Invoke({})", delegateType->DelegateSignature(), parameterString);
    }

    void InvokeContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Invoke" << std::endl;
        DynamicContextCollection::Print(indent, last);
    }
}
