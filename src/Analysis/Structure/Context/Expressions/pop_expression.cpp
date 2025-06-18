#include "pop_expression.h"

#include "../../Wrappers/Reference/object.h"

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    PopExpression::PopExpression(const IContextNode* const operand) : UnaryContextNode(Object::Instance(), operand)
    { }

    MemberType PopExpression::MemberType() const { return MemberType::PopExpression; }

    int PopExpression::SlotCount() const { return GetChild(static_cast<int>(ChildCode::Expression))->SlotCount() * 2; }

    bool PopExpression::Readable() const { return false; }
    bool PopExpression::Writable() const { return false; }

    std::string PopExpression::CILData() const { return "pop"; }

    void PopExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Pop Expression" << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}
