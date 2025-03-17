#include "invalid_function_context.h"

#include "../../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    InvalidFunctionContext::InvalidFunctionContext() : ContextNode(&Object::Instance())
    { }

    MemberType InvalidFunctionContext::MemberType() const { return MemberType::Invalid; }

    int InvalidFunctionContext::SlotCount() const { return 0; }

    bool InvalidFunctionContext::Readable() const { return false; }
    bool InvalidFunctionContext::Writable() const { return false; }

    string InvalidFunctionContext::CILData() const { return ""; }
}


