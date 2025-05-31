#include "this_context.h"

#include <iostream>

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ThisContext::ThisContext(const IDataType* const creationType) : ContextNode(creationType)
    { }

    MemberType ThisContext::MemberType() const { return MemberType::ThisContext; }

    int ThisContext::SlotCount() const { return 1; }

    bool ThisContext::Readable() const { return true; }
    bool ThisContext::Writable() const { return false; }

    string ThisContext::CILData() const { return "ldarg.0"; }

    void ThisContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "This" << std::endl;
    }
}
