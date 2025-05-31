#include "invalid_context.h"

#include "../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    InvalidContext::InvalidContext() : ContextNode(Object::Instance())
    { }

    MemberType InvalidContext::MemberType() const { return MemberType::Invalid; }

    int InvalidContext::SlotCount() const { return 0; }

    bool InvalidContext::Readable() const { return false; }
    bool InvalidContext::Writable() const { return false; }

    std::string InvalidContext::CILData() const { return ""; }

    void InvalidContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Invalid Context" << std::endl;
    }
}
