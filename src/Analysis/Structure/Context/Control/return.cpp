#include "return.h"

#include "../../Wrappers/Reference/void.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    Return::Return() : ContextNode(Void::Instance())
    { }

    Return::Return(const IDataType* const dataType) : ContextNode(dataType)
    { }

    MemberType Return::MemberType() const { return MemberType::Return; }

    int Return::SlotCount() const { return 0; }

    bool Return::Readable() const { return false; }
    bool Return::Writable() const { return false; }

    string Return::CILData() const { return "ret"; }
}
