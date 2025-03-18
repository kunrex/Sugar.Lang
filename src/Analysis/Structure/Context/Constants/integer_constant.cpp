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

    MemberType ShortConstant::MemberType() const { return MemberType::ConstantContext; }

    bool ShortConstant::Readable() const { return true; }
    bool ShortConstant::Writable() const { return false; }

    string ShortConstant::CILData() const { return std::format("ldc.i4 {}", value); }

    IntegerConstant::IntegerConstant(const int value) : ContextNode(&Integer::Instance()), value(value)
    { }

    MemberType IntegerConstant::MemberType() const { return MemberType::ConstantContext; }

    bool IntegerConstant::Readable() const { return true; }
    bool IntegerConstant::Writable() const { return false; }

    string IntegerConstant::CILData() const { return std::format("ldc.i4 {}", value); }

    LongConstant::LongConstant(const long value) : ContextNode(&Long::Instance()), value(value)
    { }

    MemberType LongConstant::MemberType() const { return MemberType::ConstantContext; }

    bool LongConstant::Readable() const { return true; }
    bool LongConstant::Writable() const { return false; }

    string LongConstant::CILData() const { return std::format("ldc.i8 {}", value); }

    CharacterConstant::CharacterConstant(const char value) : ContextNode(&Character::Instance()), value(value)
    { }

    MemberType CharacterConstant::MemberType() const { return MemberType::ConstantContext; }

    bool CharacterConstant::Readable() const { return true; }
    bool CharacterConstant::Writable() const { return false; }

    string CharacterConstant::CILData() const { return std::format("ldc.i4.s {}", static_cast<int>(value)); }

    TrueConstant::TrueConstant(): ContextNode(&Boolean::Instance())
    { }

    MemberType TrueConstant::MemberType() const { return MemberType::ConstantContext; }

    bool TrueConstant::Readable() const { return true; }
    bool TrueConstant::Writable() const { return false; }

    string TrueConstant::CILData() const { return "ldc.i4.1"; }

    FalseConstant::FalseConstant(): ContextNode(&Boolean::Instance())
    { }

    MemberType FalseConstant::MemberType() const { return MemberType::ConstantContext; }

    bool FalseConstant::Readable() const { return true; }
    bool FalseConstant::Writable() const { return false; }

    string FalseConstant::CILData() const { return "ldc.i4.0"; }
}
