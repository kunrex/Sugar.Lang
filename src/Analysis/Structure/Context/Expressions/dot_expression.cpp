#include "dot_expression.h"

using namespace std;

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    DotExpression::DotExpression(const IContextNode* const lhs, const IContextNode* const rhs) : BinaryContextNode(rhs->CreationType(),lhs, rhs), slotCount(std::max(lhs->SlotCount(), rhs->SlotCount()))
    { }

    MemberType DotExpression::MemberType() const { return MemberType::DotExpression; }

    int DotExpression::SlotCount() const { return slotCount; }

    bool DotExpression::Readable() const { return GetChild(static_cast<int>(ChildCode::RHS))->Readable(); }
    bool DotExpression::Writable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Writable() && GetChild(static_cast<int>(ChildCode::RHS))->Writable(); }

    string DotExpression::CILData() const { return ""; }
}
