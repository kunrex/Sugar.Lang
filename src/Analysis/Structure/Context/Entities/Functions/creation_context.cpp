#include "creation_context.h"

#include "function_extensions.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    CreationContext::CreationContext(const IFunction* const constructor) : DynamicContextCollection(constructor->CreationType()), slotCount(-1), constructor(constructor)
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

    MemberType CreationContext::MemberType() const { return MemberType::ConstructorCallContext; }

    bool CreationContext::Readable() const { return true; }
    bool CreationContext::Writable() const { return constructor->CreationType()->MemberType() == MemberType::Class; }

    string CreationContext::CILData() const
    {
        return constructor->FullName();
    }

    void CreationContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Creation: " << creationType->FullName() << std::endl;
        DynamicContextCollection::Print(indent, last);
    }

    CollectionCreationContext::CollectionCreationContext(const IDataType* const collectionType) : DynamicContextCollection(collectionType), slotCount(-1), collectionType(collectionType)
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

    MemberType CollectionCreationContext::MemberType() const { return MemberType::CollectorConstructorCallContext; }

    bool CollectionCreationContext::Readable() const { return true; }
    bool CollectionCreationContext::Writable() const { return creationType->MemberType() == MemberType::Class; }

    string CollectionCreationContext::CILData() const { return ""; }

    void CollectionCreationContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Creation: " << creationType->FullName() << std::endl;
        DynamicContextCollection::Print(indent, last);
    }
}
