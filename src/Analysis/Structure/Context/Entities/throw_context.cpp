#include "throw_context.h"

#include "../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ThrowContext::ThrowContext() : ContextNode(&Object::Instance())
    { }

    MemberType ThrowContext::MemberType() const { return MemberType::ThrowContext; }

    int ThrowContext::SlotCount() const { return 1; }

    bool ThrowContext::Readable() const { return false; }
    bool ThrowContext::Writable() const { return false; }

    string ThrowContext::CILData() const { return "throw"; }
}

