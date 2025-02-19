#include "dot_expression.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    DotExpression::DotExpression(const ContextNode* lhs, const ContextNode* rhs) : BinaryContextNode(rhs->CreationType(),lhs, rhs)
    {
        slotCount = std::max(lhs->SlotCount(), rhs->SlotCount());
    }

    MemberType DotExpression::MemberType() const { return MemberType::Dot; }

    bool DotExpression::Readable() const { return rhs->Readable(); }
    bool DotExpression::Writable() const { return lhs->Writable() && rhs->Writable(); }

    [[nodiscard]] std::string DotExpression::InstructionGet() const { return ""; }
    [[nodiscard]] std::string DotExpression::InstructionSet() const { return ""; }
}
