#include "string_constant.h"

#include <format>

#include "../../Wrappers/Reference/string.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    StringConstant::StringConstant(string value) : ContextNode(&String::Instance()), value(std::move(value))
    { }

    MemberType StringConstant::MemberType() const { return MemberType::Constant; }

    bool StringConstant::Readable() const { return true; }
    bool StringConstant::Writable() const { return false; }

    string StringConstant::CILInstruction() const { return std::format("ldstr {}", value); }
}
