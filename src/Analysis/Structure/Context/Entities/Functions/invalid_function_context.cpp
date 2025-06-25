#include "invalid_function_context.h"

#include "../../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    InvalidFunctionContext::InvalidFunctionContext() : DynamicContextCollection(Object::Instance())
    { }

    MemberType InvalidFunctionContext::MemberType() const { return MemberType::Invalid; }

    int InvalidFunctionContext::SlotCount() const { return 0; }

    bool InvalidFunctionContext::Readable() const { return false; }
    bool InvalidFunctionContext::Writable() const { return false; }

    std::string InvalidFunctionContext::CILData() const { return ""; }

    void InvalidFunctionContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Invalid Function Call" << std::endl;
        DynamicContextCollection::Print(indent, last);
    }
}


