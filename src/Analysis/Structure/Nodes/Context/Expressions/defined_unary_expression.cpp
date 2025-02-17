#include "defined_unary_expression.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    DefinedUnaryExpression::DefinedUnaryExpression(const OverloadDefinition* operation, const ContextNode* operand) : UnaryContextNode(operation->CreationType(), operand), cilExpression(std::format("call {}", operation->SignatureString()))
    {
        slotCount = std::max(operation->CreationType()->SlotCount(), operand->SlotCount());
    }

    MemberType DefinedUnaryExpression::MemberType() const { return MemberType::UnaryExpression; }

    bool DefinedUnaryExpression::Readable() const { return true; }
    bool DefinedUnaryExpression::Writable() const { return true; }

    std::string DefinedUnaryExpression::InstructionGet() const { return cilExpression; }
    std::string DefinedUnaryExpression::InstructionSet() const { return ""; }
}

