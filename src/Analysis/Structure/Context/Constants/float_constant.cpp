#include "float_constant.h"

#include <format>

#include "../../../Wrappers/Value/float.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    FloatConstant::FloatConstant(const float value) : ContextNode(&Float::Instance()), value(value)
    { }

    MemberType FloatConstant::MemberType() const { return MemberType::Constant; }

    bool FloatConstant::Readable() const { return true; }
    bool FloatConstant::Writable() const { return false; }

    std::string FloatConstant::InstructionGet() const { return std::format("ldc.r4 {}", value); }
    std::string FloatConstant::InstructionSet() const { return ""; }

    DoubleConstant::DoubleConstant(const double value) : ContextNode(&Float::Instance()), value(value)
    { }

    MemberType DoubleConstant::MemberType() const { return MemberType::Constant; }

    bool DoubleConstant::Readable() const { return true; }
    bool DoubleConstant::Writable() const { return false; }

    std::string DoubleConstant::InstructionGet() const { return std::format("ldc.r8 {}", value); }
    std::string DoubleConstant::InstructionSet() const { return ""; }
}
