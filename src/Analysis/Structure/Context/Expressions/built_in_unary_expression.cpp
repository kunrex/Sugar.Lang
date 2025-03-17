#include "built_in_unary_expression.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    BuiltInUnaryExpression::BuiltInUnaryExpression(const IFunction* const operation, const ContextNode* const operand) : UnaryContextNode(operation->CreationType(), operand), operation(operation)
    {
        slotCount = std::max(operation->CreationType()->SlotCount(), operand->SlotCount());
    }

    MemberType BuiltInUnaryExpression::MemberType() const { return MemberType::UnaryExpression; }

    int BuiltInUnaryExpression::SlotCount() const { return slotCount; }

    bool BuiltInUnaryExpression::Readable() const { return true; }
    bool BuiltInUnaryExpression::Writable() const { return false; }

    string BuiltInUnaryExpression::CILData() const { return operation->FullName(); }
}
