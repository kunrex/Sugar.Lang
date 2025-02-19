#include "invalid_function_context.h"

#include "../../../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    InvalidFunctionContext::InvalidFunctionContext() : ContextNode(&Object::Instance())
    { }

    MemberType InvalidFunctionContext::MemberType() const { return MemberType::Invalid; }

    bool InvalidFunctionContext::Readable() const { return false; }
    bool InvalidFunctionContext::Writable() const { return false; }

    std::string InvalidFunctionContext::InstructionGet() const { return ""; }
    std::string InvalidFunctionContext::InstructionSet() const { return ""; }
}


