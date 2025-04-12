#include "token_type.h"

using namespace std;

namespace Tokens::Enums
{
    TokenType operator | (const TokenType& lhs, const TokenType& rhs)
    {
        return static_cast<TokenType>(static_cast<short>(lhs) | static_cast<short>(rhs));
    }

    TokenType operator & (const TokenType& lhs, const TokenType& rhs)
    {
        return static_cast<TokenType>(static_cast<short>(lhs) & static_cast<short>(rhs));
    }

    string ToString(const TokenType& tokenType)
    {
        string result;
        const auto shortValue = static_cast<short>(tokenType);
        for (short i = 1; i <= static_cast<short>(TokenType::Invalid); i *= 2)
        {
            if ((shortValue & i) == i)
            {
                switch (static_cast<TokenType>(i))
                {
                    case TokenType::Keyword:
                        result += "Keyword, ";
                        break;
                    case TokenType::Invalid:
                        result += "Invalid, ";
                        break;
                    case TokenType::Constant:
                        result += "Constant, ";
                        break;
                    case TokenType::Separator:
                        result += "Separator, ";
                        break;
                    case TokenType::Identifier:
                        result += "Identifier, ";
                        break;
                    case TokenType::UnaryOperator:
                        result += "UnaryOperator, ";
                        break;
                    case TokenType::BinaryOperator:
                        result += "BinaryOperator, ";
                        break;
                    default:
                        result += "AssignmentOperator, ";
                        break;
                }
            }
        }

        return result.substr(0, result.size() - 2);
    }

    ostream& operator << (std::ostream& os, const TokenType& dt) { return os << ToString(dt); }
}