#include "invalid_funcref_context.h"

#include "../../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    InvalidFuncRefContext::InvalidFuncRefContext(const IContextNode* objectContext) : UnaryContextNode(Object::Instance(), objectContext)
    { }

    MemberType InvalidFuncRefContext::MemberType() const { return MemberType::Invalid; }

    int InvalidFuncRefContext::SlotCount() const { return 0; }

    bool InvalidFuncRefContext::Readable() const { return false; }
    bool InvalidFuncRefContext::Writable() const { return false; }

    std::string InvalidFuncRefContext::CILData() const { return ""; }

    void InvalidFuncRefContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Invlaid Function Reference" << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}
