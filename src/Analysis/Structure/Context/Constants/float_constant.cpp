#include "float_constant.h"

#include <format>

#include "../../Wrappers/Value/float.h"
#include "../../Wrappers/Value/double.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    FloatConstant::FloatConstant(const float value) : ContextNode(&Float::Instance()), value(value)
    { }

    MemberType FloatConstant::MemberType() const { return MemberType::ConstantContext; }

    int FloatConstant::SlotCount() const { return 1; }

    bool FloatConstant::Readable() const { return true; }
    bool FloatConstant::Writable() const { return false; }

    string FloatConstant::CILData() const { return std::format("ldc.r4 {}", value); }

    DoubleConstant::DoubleConstant(const double value) : ContextNode(&Double::Instance()), value(value)
    { }

    MemberType DoubleConstant::MemberType() const { return MemberType::ConstantContext; }

    int DoubleConstant::SlotCount() const { return 1; }

    bool DoubleConstant::Readable() const { return true; }
    bool DoubleConstant::Writable() const { return false; }

    string DoubleConstant::CILData() const { return std::format("ldc.r8 {}", value); }
}
