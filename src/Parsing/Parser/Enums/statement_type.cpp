#include "statement_type.h"

namespace Parsing::Enums
{
    StatementType operator&(const StatementType& lhs, const StatementType& rhs)
    {
        return static_cast<StatementType>(static_cast<short>(lhs) & static_cast<short>(rhs));
    }

    StatementType operator|(const StatementType& lhs, const StatementType& rhs)
    {
        return static_cast<StatementType>(static_cast<short>(lhs) | static_cast<short>(rhs));
    }
}
