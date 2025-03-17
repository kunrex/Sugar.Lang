#include "dot_expression.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    DotExpression::DotExpression(const ContextNode* const lhs, const ContextNode* const rhs) : BinaryContextNode(rhs->CreationType(),lhs, rhs)
    {
        slotCount = std::max(lhs->SlotCount(), rhs->SlotCount());
    }

    MemberType DotExpression::MemberType() const { return MemberType::Dot; }

    int DotExpression::SlotCount() const { return slotCount; }

    bool DotExpression::Readable() const { return rhs->Readable(); }
    bool DotExpression::Writable() const { return lhs->Writable() && rhs->Writable(); }

    string DotExpression::CILData() const { return ""; }
}
