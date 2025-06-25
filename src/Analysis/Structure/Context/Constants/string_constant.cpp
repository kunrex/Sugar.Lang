#include "string_constant.h"

#include <format>

#include "../../Wrappers/Reference/string.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    StringConstant::StringConstant(string value) : ContextNode(String::Instance()), value(std::move(value))
    { }

    int StringConstant::SlotCount() const { return 1; }

    MemberType StringConstant::MemberType() const { return MemberType::ConstantContext; }

    bool StringConstant::Readable() const { return true; }
    bool StringConstant::Writable() const { return false; }

    uintptr_t StringConstant::Metadata() const { return reinterpret_cast<uintptr_t>(&value); }
    std::string StringConstant::CILData() const { return std::format("ldstr \"{}\"", value); }

    void StringConstant::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "String Constant: " << value << std::endl;
    }
}
