#include "copy_context.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    CopyContext::CopyContext(const IContextNode* const context, const Referenced* const referenced) : UnaryContextNode(referenced->ReferencedType(), context), slotCount(std::max(1, referenced->SlotCount())), referencedType(referenced->ReferencedType())
    { }

    int CopyContext::SlotCount() const { return slotCount; }

    MemberType CopyContext::MemberType() const { return MemberType::CopyContext; }

    bool CopyContext::Readable() const { return true; }
    bool CopyContext::Writable() const { return false; }

    std::string CopyContext::CILData() const { return "ldobj " + referencedType->FullName(); }

    void CopyContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Copy" << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}
