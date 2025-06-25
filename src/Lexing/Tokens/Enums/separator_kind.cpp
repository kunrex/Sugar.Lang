#include "separator_kind.h"

#include "syntax_kind.h"

namespace Tokens::Enums
{
    SeparatorKind operator|(const SeparatorKind& lhs, const SeparatorKind& rhs)
    {
        return static_cast<SeparatorKind>(static_cast<short>(lhs) | static_cast<short>(rhs));
    }

    SeparatorKind operator&(const SeparatorKind& lhs, const SeparatorKind& rhs)
    {
        return static_cast<SeparatorKind>(static_cast<short>(lhs) & static_cast<short>(rhs));
    }

    std::string ToString(const SeparatorKind& separatorKind)
    {
        std::string result;
        const auto shortValue = static_cast<short>(separatorKind);
        for (short i = 1; i <= static_cast<short>(SeparatorKind::None); i *= 2)
        {
            if ((shortValue & i) == i)
            {
                result += ToString(static_cast<SyntaxKind>(i));
                result += ", ";
            }

        }

        return result.substr(0, result.size() - 2);
    }

    std::ostream& operator<<(std::ostream& os, const SeparatorKind& dt) { return os << ToString(dt); }
}
