#include "defined_unary_expression.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    DefinedUnaryExpression::DefinedUnaryExpression(const IFunction* const operation, const IContextNode* const operand) : UnaryContextNode(operation->CreationType(), operand), slotCount(std::max(operand->CreationType()->SlotCount(), operand->SlotCount())), operation(operation)
    { }

    MemberType DefinedUnaryExpression::MemberType() const { return MemberType::UnaryExpression; }

    int DefinedUnaryExpression::SlotCount() const { return slotCount; }

    bool DefinedUnaryExpression::Readable() const { return true; }
    bool DefinedUnaryExpression::Writable() const { return true; }

    string DefinedUnaryExpression::CILData() const { return operation->MemberType() == MemberType::BuiltInOperation ? operation->FullName() : std::format("call {}", operation->FullName()); }
}

