#include "throw.h"

#include "../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    Throw::Throw() : ContextNode(&Object::Instance())
    { }

    MemberType Throw::MemberType() const { return MemberType::Throw; }

    int Throw::SlotCount() const { return 0; }

    bool Throw::Readable() const { return false; }
    bool Throw::Writable() const { return false; }

    string Throw::CILData() const { return "ret"; }
}

