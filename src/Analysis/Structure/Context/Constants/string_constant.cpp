#include "string_constant.h"

#include <format>

#include "../../../Wrappers/Reference/string.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    StringConstant::StringConstant(const std::string_view value) : ContextNode(&String::Instance()), value(value)
    { }

    MemberType StringConstant::MemberType() const { return MemberType::Constant; }

    bool StringConstant::Readable() const { return true; }
    bool StringConstant::Writable() const { return false; }

    std::string StringConstant::InstructionGet() const { return std::format("ldstr {}", value); }
    std::string StringConstant::InstructionSet() const { return ""; }
}
