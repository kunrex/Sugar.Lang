#include "ref_context.h"

#include "../../../Wrappers/Generic/referenced.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    RefContext::RefContext(const IContextNode* const context) : UnaryContextNode(Referenced::Instance(context->CreationType()), context), slotCount(std::max(1, context->CreationType()->SlotCount()))
    { }

    int RefContext::SlotCount() const { return slotCount; }

    MemberType RefContext::MemberType() const { return MemberType::CopyContext; }

    bool RefContext::Readable() const { return true; }
    bool RefContext::Writable() const { return false; }

    std::string RefContext::CILData() const { return ""; }

    void RefContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Ref" << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}

