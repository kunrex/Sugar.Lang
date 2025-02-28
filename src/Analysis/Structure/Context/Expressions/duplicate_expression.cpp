#include "duplicate_expression.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    DuplicateExpression::DuplicateExpression(const ContextNode* const operand) : UnaryContextNode(operand->CreationType(), operand)
    { }

    MemberType DuplicateExpression::MemberType() const { return MemberType::Dot; }

    int DuplicateExpression::SlotCount() const { return operand->SlotCount() * 2; }

    bool DuplicateExpression::Readable() const { return operand->Readable(); }
    bool DuplicateExpression::Writable() const { return operand->Writable(); }

    string DuplicateExpression::CILInstruction() const { return "dup"; }
}

