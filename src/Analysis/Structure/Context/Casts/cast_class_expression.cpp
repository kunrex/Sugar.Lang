#include "cast_class_expression.h"

#include <format>

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    CastClassExpression::CastClassExpression(const IDataType* const creationType, const IContextNode* const operand) : UnaryContextNode(creationType, operand), slotCount(std::max(operand->CreationType()->SlotCount(), creationType->SlotCount()))
    { }

    MemberType CastClassExpression::MemberType() const { return MemberType::CastExpression; }

    int CastClassExpression::SlotCount() const { return slotCount; }

    bool CastClassExpression::Readable() const { return true; }
    bool CastClassExpression::Writable() const { return false; }

    string CastClassExpression::CILData() const { return std::format("castclass {}", creationType->FullName()); }
}
