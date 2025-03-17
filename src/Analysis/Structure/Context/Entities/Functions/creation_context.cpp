#include "creation_context.h"

#include "function_extensions.h"
#include "../../../Global/BuiltIn/built_in_constructor.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    CreationContext::CreationContext(const IFunction* constructor) : ContextNode(constructor->CreationType()), slotCount(-1), constructor(constructor)
    { }

    int CreationContext::SlotCount() const
    {
        if (slotCount < 0)
        {
            slotCount = CalculateFunctionCallSlotSize(this);

            if (creationType != nullptr)
                slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }

    MemberType CreationContext::MemberType() const { return MemberType::FunctionCallContext; }

    bool CreationContext::Readable() const { return true; }
    bool CreationContext::Writable() const { return constructor->CreationType()->MemberType() == MemberType::Class; }

    string CreationContext::CILData() const
    {
        if (constructor->MemberType() == MemberType::BuiltInConstructor)
            return constructor->FullName();

        return "call " + constructor->FullName();
    }

    CollectionCreationContext::CollectionCreationContext(const ICollectionType* collectionType) : ContextNode(collectionType), slotCount(-1), constructorCIL(collectionType->ConstructorSignature()), pushElementCIL(collectionType->PushElementSignature())
    { }

    int CollectionCreationContext::SlotCount() const
    {
        if (slotCount < 0)
        {
            slotCount = CalculateFunctionCallSlotSize(this);

            if (creationType != nullptr)
                slotCount = std::max(creationType->SlotCount(), slotCount);
        }

        return slotCount;
    }

    MemberType CollectionCreationContext::MemberType() const { return MemberType::FunctionCallContext; }

    bool CollectionCreationContext::Readable() const { return true; }
    bool CollectionCreationContext::Writable() const { return creationType->MemberType() == MemberType::Class; }

    string CollectionCreationContext::CILData() const { return ""; }

    const string& CollectionCreationContext::ConstructorCIL() const { return constructorCIL; }
    const string& CollectionCreationContext::PushElementCIL() const { return pushElementCIL; }
}
