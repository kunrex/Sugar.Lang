#include "invalid_funcref_context.h"

#include "../../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    InvalidFuncRefContext::InvalidFuncRefContext(const ContextNode* objectContext) : UnaryContextNode(&Object::Instance(), objectContext)
    { }

    MemberType InvalidFuncRefContext::MemberType() const { return MemberType::Invalid; }

    int InvalidFuncRefContext::SlotCount() const { return 0; }

    bool InvalidFuncRefContext::Readable() const { return false; }
    bool InvalidFuncRefContext::Writable() const { return false; }

    string InvalidFuncRefContext::CILData() const { return ""; }
}
