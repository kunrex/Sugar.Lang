#include "built_in_binary_expression.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    BuiltInBinaryExpression::BuiltInBinaryExpression(const OverloadDefinition* operation, const ContextNode* lhs, const ContextNode* rhs) : BinaryContextNode(operation->CreationType(), lhs, rhs), cilExpression(operation->SignatureString())
    {
        slotCount = std::max(operation->CreationType()->SlotCount(), std::max(lhs->SlotCount(), rhs->SlotCount()));
    }

    MemberType BuiltInBinaryExpression::MemberType() const { return MemberType::BinaryExpression; }

    bool BuiltInBinaryExpression::Readable() const { return true; }

    bool BuiltInBinaryExpression::Writable() const { return false; }

    std::string BuiltInBinaryExpression::InstructionGet() const { return cilExpression; }
    std::string BuiltInBinaryExpression::InstructionSet() const { return ""; }
}
