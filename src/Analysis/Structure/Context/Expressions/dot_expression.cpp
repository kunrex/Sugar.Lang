#include "dot_expression.h"

#include <iostream>

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    DotExpression::DotExpression(const IContextNode* const lhs, const IContextNode* const rhs) : BinaryContextNode(rhs->CreationType(),lhs, rhs), slotCount(std::max(lhs->SlotCount(), rhs->SlotCount()))
    { }

    MemberType DotExpression::MemberType() const { return MemberType::DotExpression; }

    int DotExpression::SlotCount() const { return slotCount; }

    bool DotExpression::Readable() const { return GetChild(static_cast<int>(ChildCode::RHS))->Readable(); }
    bool DotExpression::Writable() const { return GetChild(static_cast<int>(ChildCode::RHS))->Writable(); }

    std::string DotExpression::CILData() const { return ""; }

    void DotExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Dot Expression" << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}
