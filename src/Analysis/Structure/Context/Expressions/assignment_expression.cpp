#include "assignment_expression.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    AssignmentExpression::AssignmentExpression(const ContextNode* const lhs, const ContextNode* const rhs) : BinaryContextNode(lhs->CreationType(), lhs, rhs)
    {
        slotCount = std::max(lhs->SlotCount(), rhs->SlotCount());
    }

    MemberType AssignmentExpression::MemberType() const { return MemberType::AssignmentOperation; }

    int AssignmentExpression::SlotCount() const { return slotCount; }

    bool AssignmentExpression::Readable() const { return lhs->Readable(); }
    bool AssignmentExpression::Writable() const { return lhs->Writable(); }

    string AssignmentExpression::CILData() const { return ""; }
}
