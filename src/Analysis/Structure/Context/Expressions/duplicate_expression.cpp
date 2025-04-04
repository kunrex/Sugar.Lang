#include "duplicate_expression.h"

using namespace std;

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    DuplicateExpression::DuplicateExpression(const IContextNode* const operand) : UnaryContextNode(operand->CreationType(), operand)
    { }

    MemberType DuplicateExpression::MemberType() const { return MemberType::DuplicateExpression; }

    int DuplicateExpression::SlotCount() const { return GetChild(static_cast<int>(ChildCode::Expression))->SlotCount() * 2; }

    bool DuplicateExpression::Readable() const { return GetChild(static_cast<int>(ChildCode::Expression))->Readable(); }
    bool DuplicateExpression::Writable() const { return GetChild(static_cast<int>(ChildCode::Expression))->Writable(); }

    string DuplicateExpression::CILData() const { return "dup"; }
}

