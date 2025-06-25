#include "return.h"

#include "../../Wrappers/Reference/void.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    Return::Return() : UnaryContextNode(Void::Instance(), nullptr), slotCount(0)
    { }

    Return::Return(const IContextNode* const expression) : UnaryContextNode(expression->CreationType(), expression), slotCount(expression->SlotCount())
    { }

    MemberType Return::MemberType() const { return MemberType::Return; }

    int Return::SlotCount() const { return slotCount; }

    bool Return::Readable() const { return false; }
    bool Return::Writable() const { return false; }

    std::string Return::CILData() const { return "ret"; }

    void Return::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Return" << std::endl;
        if (const auto child = GetChild(static_cast<int>(ParseNodes::Enums::ChildCode::Expression)); child != nullptr)
            child->Print(indent + " ", true);
    }
}
