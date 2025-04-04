#include "assignment_expression.h"

using namespace std;

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    AssignmentExpression::AssignmentExpression(const IContextNode* const lhs, const IContextNode* const rhs) : BinaryContextNode(lhs->CreationType(), lhs, rhs), slotCount(std::max(lhs->SlotCount(), rhs->SlotCount()))
    { }

    MemberType AssignmentExpression::MemberType() const { return MemberType::AssignmentExpression; }

    int AssignmentExpression::SlotCount() const { return slotCount; }

    bool AssignmentExpression::Readable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Readable(); }
    bool AssignmentExpression::Writable() const { return GetChild(static_cast<int>(ChildCode::LHS))->Writable(); }

    string AssignmentExpression::CILData() const { return ""; }
}
