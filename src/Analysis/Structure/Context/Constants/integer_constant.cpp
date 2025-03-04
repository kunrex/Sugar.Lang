#include "integer_constant.h"

#include <format>

#include "../../Wrappers/Value/short.h"
#include "../../Wrappers/Value/integer.h"
#include "../../Wrappers/Value/long.h"
#include "../../Wrappers/Value/boolean.h"
#include "../../Wrappers/Value/character.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    ShortConstant::ShortConstant(const short value) : ContextNode(&Short::Instance()), value(value)
    { }

    MemberType ShortConstant::MemberType() const { return MemberType::Constant; }

    bool ShortConstant::Readable() const { return true; }
    bool ShortConstant::Writable() const { return false; }

    string ShortConstant::CILInstruction() const { return std::format("ldc.i4 {}", value); }

    IntegerConstant::IntegerConstant(const int value) : ContextNode(&Integer::Instance()), value(value)
    { }

    MemberType IntegerConstant::MemberType() const { return MemberType::Constant; }

    bool IntegerConstant::Readable() const { return true; }
    bool IntegerConstant::Writable() const { return false; }

    string IntegerConstant::CILInstruction() const { return std::format("ldc.i4 {}", value); }

    LongConstant::LongConstant(const long value) : ContextNode(&Long::Instance()), value(value)
    { }

    MemberType LongConstant::MemberType() const { return MemberType::Constant; }

    bool LongConstant::Readable() const { return true; }
    bool LongConstant::Writable() const { return false; }

    string LongConstant::CILInstruction() const { return std::format("ldc.i8 {}", value); }

    CharacterConstant::CharacterConstant(const char value) : ContextNode(&Character::Instance()), value(value)
    { }

    MemberType CharacterConstant::MemberType() const { return MemberType::Constant; }

    bool CharacterConstant::Readable() const { return true; }
    bool CharacterConstant::Writable() const { return false; }

    string CharacterConstant::CILInstruction() const { return std::format("ldc.i4.s {}", static_cast<int>(value)); }

    TrueConstant::TrueConstant(): ContextNode(&Boolean::Instance())
    { }

    MemberType TrueConstant::MemberType() const { return MemberType::Constant; }

    bool TrueConstant::Readable() const { return true; }
    bool TrueConstant::Writable() const { return false; }

    string TrueConstant::CILInstruction() const { return "ldc.i4.1"; }

    FalseConstant::FalseConstant(): ContextNode(&Boolean::Instance())
    { }

    MemberType FalseConstant::MemberType() const { return MemberType::Constant; }

    bool FalseConstant::Readable() const { return true; }
    bool FalseConstant::Writable() const { return false; }

    string FalseConstant::CILInstruction() const { return "ldc.i4.0"; }
}
