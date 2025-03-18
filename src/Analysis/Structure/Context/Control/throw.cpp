#include "throw.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    Throw::Throw(const ContextNode* const operand) : UnaryContextNode(operand->CreationType(), operand)
    { }

    MemberType Throw::MemberType() const { return MemberType::Throw; }

    int Throw::SlotCount() const { return 0; }

    bool Throw::Readable() const { return false; }
    bool Throw::Writable() const { return false; }

    string Throw::CILData() const { return "ret"; }
}

