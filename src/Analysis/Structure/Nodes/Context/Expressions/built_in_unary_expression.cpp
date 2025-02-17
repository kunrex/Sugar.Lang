#include "built_in_unary_expression.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    BuiltInUnaryExpression::BuiltInUnaryExpression(const OverloadDefinition* operation, const ContextNode* operand) : UnaryContextNode(operation->CreationType(), operand), cilExpression(operation->SignatureString())
    {
        slotCount = std::max(operation->CreationType()->SlotCount(), operand->SlotCount());
    }

    MemberType BuiltInUnaryExpression::MemberType() const { return MemberType::UnaryExpression; }

    bool BuiltInUnaryExpression::Readable() const { return true; }
    bool BuiltInUnaryExpression::Writable() const { return false; }

    std::string BuiltInUnaryExpression::InstructionGet() const { return cilExpression; }
    std::string BuiltInUnaryExpression::InstructionSet() const { return ""; }
}
