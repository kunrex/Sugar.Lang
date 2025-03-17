#include "copy_context.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    CopyContext::CopyContext(const ContextNode* const context, const Referenced* const referenced) : UnaryContextNode(referenced->ReferencedType(), context), referencedType(referenced->ReferencedType())
    {
        slotCount = std::max(1, referencedType->SlotCount());
    }

    int CopyContext::SlotCount() const { return slotCount; }

    MemberType CopyContext::MemberType() const { return MemberType::CopyContext; }

    bool CopyContext::Readable() const { return true; }
    bool CopyContext::Writable() const { return false; }

    std::string CopyContext::CILData() const { return "ldobj " + referencedType->FullName(); }
}
