#include "null_constant.h"

#include <format>

#include "../../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    NullConstant::NullConstant() : ContextNode(&Object::Instance())
    { }

    MemberType NullConstant::MemberType() const { return MemberType::Constant; }

    bool NullConstant::Readable() const { return true; }
    bool NullConstant::Writable() const { return false; }

    std::string NullConstant::InstructionGet() const { return "ldnull"; }
    std::string NullConstant::InstructionSet() const { return ""; }
}
