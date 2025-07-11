#include "throw.h"

#include "../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    Throw::Throw() : ContextNode(Object::Instance())
    { }

    MemberType Throw::MemberType() const { return MemberType::Throw; }

    int Throw::SlotCount() const { return 0; }

    bool Throw::Readable() const { return false; }
    bool Throw::Writable() const { return false; }

    std::string Throw::CILData() const { return "ret"; }

    void Throw::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Throw" << std::endl;
    }
}

