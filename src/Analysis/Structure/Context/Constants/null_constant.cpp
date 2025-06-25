#include "null_constant.h"

#include "../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    NullConstant::NullConstant() : ContextNode(Object::Instance())
    { }

    MemberType NullConstant::MemberType() const { return MemberType::NullConstantContext; }

    int NullConstant::SlotCount() const { return 1; }

    bool NullConstant::Readable() const { return true; }
    bool NullConstant::Writable() const { return false; }

    std::string NullConstant::CILData() const { return "ldnull"; }

    void NullConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Null Constant" << std::endl;
    }
}
