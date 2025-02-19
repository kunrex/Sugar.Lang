#include "print.h"

#include <format>

using namespace Analysis::Structure::Enums;

constexpr std::string_view cil_write = "call void [mscorlib]System.Console::Write";
constexpr std::string_view cil_write_line = "call void [mscorlib]System.Console::WriteLine";

namespace Analysis::Structure::Context
{
    Print::Print(const bool ln) : ContextNode(nullptr), Collection(), ln(ln), operand(nullptr)
    {
        slotCount = -1;;
    }

    Print::Print(const ContextNode* const operand, const bool ln):  ContextNode(nullptr), Collection(), ln(ln), operand(operand)
    {
        slotCount = operand->SlotCount();
    }

    MemberType Print::MemberType() const { return MemberType::PrintContext; }

    const ContextNode* Print::Operand() const { return operand; }

    bool Print::Readable() const { return false; }
    bool Print::Writable() const { return false; }

    std::string Print::InstructionGet() const { return std::format("{}()", cil_write); }
    std::string Print::InstructionSet() const { return ""; }

    int Print::SlotCount() const
    {
        if (slotCount == -1)
        {
            if (children.empty())
                slotCount = 0;
            else
                slotCount = children.at(0)->SlotCount();
        }

        return slotCount;
    }

    PrintChar::PrintChar(const bool ln) : Print(ln)
    { }

    PrintChar::PrintChar(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintChar::InstructionGet() const { return std::format("{}(char)", ln ? cil_write : cil_write_line); }

    PrintBool::PrintBool(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintBool::InstructionGet() const { return std::format("{}(bool)", ln ? cil_write : cil_write_line); }

    PrintShort::PrintShort(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintShort::InstructionGet() const { return std::format("{}(int16)", ln ? cil_write : cil_write_line); }

    PrintInt::PrintInt(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintInt::InstructionGet() const { return std::format("{}(int32)", ln ? cil_write : cil_write_line); }

    PrintLong::PrintLong(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintLong::InstructionGet() const { return std::format("{}(int64)", ln ? cil_write : cil_write_line); }

    PrintFloat::PrintFloat(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintFloat::InstructionGet() const { return std::format("{}(float32)", ln ? cil_write : cil_write_line); }

    PrintDouble::PrintDouble(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintDouble::InstructionGet() const { return std::format("{}(float64)", ln ? cil_write : cil_write_line); }

    PrintString::PrintString(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintString::InstructionGet() const { return std::format("{}(string)", ln ? cil_write : cil_write_line); }

    PrintObject::PrintObject(const ContextNode* const operand, const bool ln) : Print(operand, ln)
    { }

    std::string PrintObject::InstructionGet() const { return std::format("{}(object)", ln ? cil_write : cil_write_line); }
}
