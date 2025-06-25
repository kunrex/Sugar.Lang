#include "static_reference_context.h"

#include <iostream>

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    StaticReferenceContext::StaticReferenceContext(const IDataType* const creationType) : ContextNode(creationType)
    { }

    MemberType StaticReferenceContext::MemberType() const { return MemberType::StaticReferenceContext; }

    int StaticReferenceContext::SlotCount() const { return 0; }

    bool StaticReferenceContext::Readable() const { return true; }
    bool StaticReferenceContext::Writable() const { return false; }

    std::string StaticReferenceContext::CILData() const { return ""; }

    void StaticReferenceContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << "Static Reference: " << creationType->FullName() << std::endl;
    }
}