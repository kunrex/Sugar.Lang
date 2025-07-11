#include "integer_constant.h"

#include <format>

#include "../../Wrappers/Value/long.h"
#include "../../Wrappers/Value/short.h"
#include "../../Wrappers/Value/integer.h"
#include "../../Wrappers/Value/boolean.h"
#include "../../Wrappers/Value/character.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    ShortConstant::ShortConstant(const short value) : ContextNode(Short::Instance()), value(value)
    { }

    MemberType ShortConstant::MemberType() const { return MemberType::ConstantContext; }

    int ShortConstant::SlotCount() const { return 1; }

    bool ShortConstant::Readable() const { return true; }
    bool ShortConstant::Writable() const { return false; }

    uintptr_t ShortConstant::Metadata() const { return reinterpret_cast<uintptr_t>(&value); }
    std::string ShortConstant::CILData() const { return std::format("ldc.i4 {}", value); }

    void ShortConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Short Constant: " << value << std::endl;
    }

    IntegerConstant::IntegerConstant(const int value) : ContextNode(Integer::Instance()), value(value)
    { }

    MemberType IntegerConstant::MemberType() const { return MemberType::ConstantContext; }

    int IntegerConstant::SlotCount() const { return 1; }

    bool IntegerConstant::Readable() const { return true; }
    bool IntegerConstant::Writable() const { return false; }

    uintptr_t IntegerConstant::Metadata() const { return reinterpret_cast<uintptr_t>(&value); }
    std::string IntegerConstant::CILData() const { return std::format("ldc.i4 {}", value); }

    void IntegerConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Integer Constant: " << value << std::endl;
    }

    LongConstant::LongConstant(const long value) : ContextNode(Long::Instance()), value(value)
    { }

    MemberType LongConstant::MemberType() const { return MemberType::ConstantContext; }

    int LongConstant::SlotCount() const { return 1; }

    bool LongConstant::Readable() const { return true; }
    bool LongConstant::Writable() const { return false; }

    uintptr_t LongConstant::Metadata() const { return reinterpret_cast<uintptr_t>(&value); }
    std::string LongConstant::CILData() const { return std::format("ldc.i8 {}", value); }

    void LongConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Long Constant: " << value << std::endl;
    }

    CharacterConstant::CharacterConstant(const char value) : ContextNode(Character::Instance()), value(value)
    { }

    MemberType CharacterConstant::MemberType() const { return MemberType::ConstantContext; }

    int CharacterConstant::SlotCount() const { return 1; }

    bool CharacterConstant::Readable() const { return true; }
    bool CharacterConstant::Writable() const { return false; }

    uintptr_t CharacterConstant::Metadata() const { return reinterpret_cast<uintptr_t>(&value); }
    std::string CharacterConstant::CILData() const { return std::format("ldc.i4.s {}", static_cast<int>(value)); }

    void CharacterConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Character Constant: " << value << std::endl;
    }

    BoolConstant::BoolConstant(const bool value) : ContextNode(Boolean::Instance()), value(value)
    { }

    void BoolConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Bool Constant: " << value << std::endl;
    }

    uintptr_t BoolConstant::Metadata() const { return reinterpret_cast<uintptr_t>(&value); }

    TrueConstant::TrueConstant(): BoolConstant(true)
    { }

    MemberType TrueConstant::MemberType() const { return MemberType::ConstantContext; }

    int TrueConstant::SlotCount() const { return 1; }

    bool TrueConstant::Readable() const { return true; }
    bool TrueConstant::Writable() const { return false; }

    std::string TrueConstant::CILData() const { return "ldc.i4.1"; }

    FalseConstant::FalseConstant(): BoolConstant(false)
    { }

    MemberType FalseConstant::MemberType() const { return MemberType::ConstantContext; }

    int FalseConstant::SlotCount() const { return 1; }

    bool FalseConstant::Readable() const { return true; }
    bool FalseConstant::Writable() const { return false; }

    std::string FalseConstant::CILData() const { return "ldc.i4.0"; }
}
