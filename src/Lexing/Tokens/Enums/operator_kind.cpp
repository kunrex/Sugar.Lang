#include "operator_kind.h"

namespace Tokens::Enums
{
    OperatorKind operator|(const OperatorKind& lhs, const OperatorKind& rhs)
    {
        return static_cast<OperatorKind>(static_cast<short>(lhs) | static_cast<short>(rhs));
    }

    OperatorKind operator&(const OperatorKind& lhs, const OperatorKind& rhs)
    {
        return static_cast<OperatorKind>(static_cast<short>(lhs) & static_cast<short>(rhs));
    }

    OperatorKind operator^(const OperatorKind& lhs, const OperatorKind& rhs)
    {
        return static_cast<OperatorKind>(static_cast<short>(lhs) ^ static_cast<short>(rhs));
    }
}
