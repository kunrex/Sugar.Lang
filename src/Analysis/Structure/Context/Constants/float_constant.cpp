#include "float_constant.h"

#include <format>

#include "../../Wrappers/Value/float.h"
#include "../../Wrappers/Value/double.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    FloatConstant::FloatConstant(const float value) : ContextNode(Float::Instance()), value(value)
    { }

    MemberType FloatConstant::MemberType() const { return MemberType::ConstantContext; }

    int FloatConstant::SlotCount() const { return 1; }

    bool FloatConstant::Readable() const { return true; }
    bool FloatConstant::Writable() const { return false; }

    uintptr_t FloatConstant::Metadata() const { return reinterpret_cast<uintptr_t>(&value); }
    string FloatConstant::CILData() const { return std::format("ldc.r4 {}", value); }

    void FloatConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Float Constant: " << value << std::endl;
    }

    DoubleConstant::DoubleConstant(const double value) : ContextNode(Double::Instance()), value(value)
    { }

    MemberType DoubleConstant::MemberType() const { return MemberType::ConstantContext; }

    int DoubleConstant::SlotCount() const { return 1; }

    bool DoubleConstant::Readable() const { return true; }
    bool DoubleConstant::Writable() const { return false; }

    uintptr_t DoubleConstant::Metadata() const { return reinterpret_cast<uintptr_t>(&value); }
    string DoubleConstant::CILData() const { return std::format("ldc.r8 {}", value); }

    void DoubleConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Double Constant: " << value << std::endl;
    }
}
