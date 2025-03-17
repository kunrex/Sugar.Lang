#include "null_constant.h"

#include "../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    NullConstant::NullConstant() : ContextNode(&Object::Instance())
    { }

    MemberType NullConstant::MemberType() const { return MemberType::Constant; }

    int NullConstant::SlotCount() const { return 0; }

    bool NullConstant::Readable() const { return true; }
    bool NullConstant::Writable() const { return false; }

    string NullConstant::CILData() const { return "ldnull"; }
}
