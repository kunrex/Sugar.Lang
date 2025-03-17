#include "print_context.h"

#include <format>

#include "../../../Wrappers/Reference/object.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

constexpr std::string_view cil_write = "call void [System.Runtime]System.Console::Write";
constexpr std::string_view cil_write_line = "call void [System.Runtime]System.Console::WriteLine";

namespace Analysis::Structure::Context
{
    PrintContext::PrintContext(const bool ln) : UnaryContextNode(&Object::Instance(), nullptr), ln(ln), slotCount(0)
    { }

    PrintContext::PrintContext(const ContextNode* const operand, const bool ln) : UnaryContextNode(&Object::Instance(), operand), ln(ln), slotCount(operand->SlotCount())
    { }

    MemberType PrintContext::MemberType() const { return MemberType::PrintContext; }

    int PrintContext::SlotCount() const { return slotCount; }

    bool PrintContext::Readable() const { return false; }
    bool PrintContext::Writable() const { return false; }

    string PrintContext::CILData() const { return std::format("{}()", ln ? cil_write : cil_write_line); }

    PrintCharContext::PrintCharContext(const bool ln) : PrintContext(ln)
    { }

    PrintCharContext::PrintCharContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintCharContext::CILData() const { return std::format("{}(char)", ln ? cil_write : cil_write_line); }

    PrintBoolContext::PrintBoolContext(const bool ln) : PrintContext(ln)
    { }

    PrintBoolContext::PrintBoolContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintBoolContext::CILData() const { return std::format("{}(bool)", ln ? cil_write : cil_write_line); }

    PrintShortContext::PrintShortContext(const bool ln) : PrintContext(ln)
    { }

    PrintShortContext::PrintShortContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintShortContext::CILData() const { return std::format("{}(int16)", ln ? cil_write : cil_write_line); }

    PrintIntContext::PrintIntContext(const bool ln) : PrintContext(ln)
    { }

    PrintIntContext::PrintIntContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintIntContext::CILData() const { return std::format("{}(int32)", ln ? cil_write : cil_write_line); }

    PrintLongContext::PrintLongContext(const bool ln) : PrintContext(ln)
    { }

    PrintLongContext::PrintLongContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintLongContext::CILData() const { return std::format("{}(int64)", ln ? cil_write : cil_write_line); }

    PrintFloatContext::PrintFloatContext(const bool ln) : PrintContext(ln)
    { }

    PrintFloatContext::PrintFloatContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintFloatContext::CILData() const { return std::format("{}(float32)", ln ? cil_write : cil_write_line); }

    PrintDoubleContext::PrintDoubleContext(const bool ln) : PrintContext(ln)
    { }

    PrintDoubleContext::PrintDoubleContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintDoubleContext::CILData() const { return std::format("{}(float64)", ln ? cil_write : cil_write_line); }

    PrintStringContext::PrintStringContext(const bool ln) : PrintContext(ln)
    { }

    PrintStringContext::PrintStringContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintStringContext::CILData() const { return std::format("{}(string)", ln ? cil_write : cil_write_line); }

    PrintObjectContext::PrintObjectContext(const bool ln) : PrintContext(ln)
    { }

    PrintObjectContext::PrintObjectContext(const ContextNode* const operand, const bool ln) : PrintContext(operand, ln)
    { }

    string PrintObjectContext::CILData() const { return std::format("{}(object)", ln ? cil_write : cil_write_line); }
}
