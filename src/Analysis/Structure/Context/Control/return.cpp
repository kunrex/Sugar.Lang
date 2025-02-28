#include "return.h"

#include "../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    Return::Return() : ContextNode(&Object::Instance())
    { }

    Return::Return(const DataType* const dataType) : ContextNode(dataType)
    { }

    MemberType Return::MemberType() const { return MemberType::Return; }

    int Return::SlotCount() const { return 0; }

    bool Return::Readable() const { return false; }
    bool Return::Writable() const { return false; }

    string Return::CILInstruction() const { return "ret"; }
}
