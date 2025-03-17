#include "operator.h"

using namespace Tokens::Enums;

namespace Tokens
{
    Operator::Operator() = default;

    short Operator::EncodeMetadata(const bool leftAssociative, const int precedence)
    {
        return static_cast<short>((leftAssociative << 8) | precedence);
    }

    std::tuple<bool, int> Operator::DecodeMetadata(const Token& token)
    {
        const auto metadata = token.Metadata();
        return { (metadata >> 8) & 0xFF, metadata & 0xFF };
    }

    std::optional<SyntaxKind> Operator::IsAssignment(const SyntaxKind kind)
    {
        const auto operatorKind = static_cast<OperatorKind>(kind);
        return (operatorKind & OperatorKind::Assignment) == OperatorKind::Assignment ? std::make_optional(static_cast<SyntaxKind>(operatorKind ^ OperatorKind::Assignment)) : std::nullopt;
    }

    Token Operator::Unary(const unsigned long index, const SyntaxKind syntaxKind, const std::string& value, const bool leftAssociative, const int precedence)
    {
        return { index, TokenType::UnaryOperator, syntaxKind, EncodeMetadata(leftAssociative, precedence), value };
    }

    Token Operator::Binary(const unsigned long index, const SyntaxKind syntaxKind, const std::string& value, const int precedence)
    {
        return { index, TokenType::BinaryOperator, syntaxKind, EncodeMetadata(true, precedence), value };
    }

    Token Operator::Assignment(const unsigned long index, const SyntaxKind syntaxKind, const std::string& value)
    {
        return { index, TokenType::BinaryOperator, syntaxKind, 13, value };
    }

    Token Operator::Addition(const unsigned long i) { return Binary(i, SyntaxKind::Addition, "+", 4); }
    Token Operator::Subtraction(const unsigned long i) { return Binary(i, SyntaxKind::Subtraction, "-", 4); }

    Token Operator::Multiplication(const unsigned long i) { return Binary(i, SyntaxKind::Multiplication, "*", 3); }
    Token Operator::Division(const unsigned long i) { return Binary(i, SyntaxKind::Addition, "/", 3); }
    Token Operator::Modulus(const unsigned long i) { return Binary(i, SyntaxKind::Addition, "%", 3); }

    Token Operator::And(const unsigned long i) { return Binary(i, SyntaxKind::And, "&&", 11); }
    Token Operator::Or(const unsigned long i) { return Binary(i, SyntaxKind::Or, "||", 12); }

    Token Operator::BitwiseAnd(const unsigned long i) { return Binary(i, SyntaxKind::BitwiseAnd, "&", 8); }
    Token Operator::BitwiseOr(const unsigned long i) { return Binary(i, SyntaxKind::BitwiseOr, "|", 10); }
    Token Operator::BitwiseXor(const unsigned long i) { return Binary(i, SyntaxKind::BitwiseXor, "^", 9); }
    Token Operator::RightShift(const unsigned long i) { return Binary(i, SyntaxKind::RightShift, ">>", 5); }
    Token Operator::LeftShift(const unsigned long i) { return Binary(i, SyntaxKind::LeftShift, "<<", 5); }

    Token Operator::Equals(const unsigned long i) { return Binary(i, SyntaxKind::Equals, "==", 8); }
    Token Operator::NotEquals(const unsigned long i) { return Binary(i, SyntaxKind::NotEquals, "!=", 10); }
    Token Operator::LesserThan(const unsigned long i) { return Binary(i, SyntaxKind::LesserThan, "<", 9); }
    Token Operator::GreaterThan(const unsigned long i) { return Binary(i, SyntaxKind::GreaterThan, ">", 5); }
    Token Operator::LesserThanEquals(const unsigned long i) { return Binary(i, SyntaxKind::LesserThanEquals, "<=", 5); }
    Token Operator::GreaterThanEquals(const unsigned long i) { return Binary(i, SyntaxKind::GreaterThanEquals, ">=", 5); }

    Token Operator::Increment(const unsigned long i) { return Unary(i, SyntaxKind::Increment, "++", true, 0); }
    Token Operator::Decrement(const unsigned long i) { return Unary(i, SyntaxKind::Decrement, "++", true, 0); }

    Token Operator::IncrementPrefix(const unsigned long i) { return Unary(i, SyntaxKind::IncrementPrefix, "++", true, 0); }
    Token Operator::DecrementPrefix(const unsigned long i) { return Unary(i, SyntaxKind::DecrementPrefix, "++", true, 0); }

    Token Operator::Not(const unsigned long i) { return Unary(i, SyntaxKind::Not, "++", false, 2); }
    Token Operator::Plus(const unsigned long i) { return Unary(i, SyntaxKind::Plus, "++", false, 2); }
    Token Operator::Minus(const unsigned long i) { return Unary(i, SyntaxKind::Minus, "++", false, 2); }
    Token Operator::BitwiseNot(const unsigned long i) { return Unary(i, SyntaxKind::DecrementPrefix, "~", false, 2); }

    Token Operator::Assignment(const unsigned long i) { return Assignment(i, SyntaxKind::AssignmentAddition, "+="); }

    Token Operator::AssignmentAddition(const unsigned long i) { return Assignment(i, SyntaxKind::AssignmentAddition, "+="); }
    Token Operator::AssignmentSubtraction(const unsigned long i) { return Assignment(i, SyntaxKind::AssignmentSubtraction, "-="); }

    Token Operator::AssignmentMultiplication(const unsigned long i) { return Assignment(i, SyntaxKind::AssignmentMultiplication, "*="); }
    Token Operator::AssignmentDivision(const unsigned long i) { return Assignment(i, SyntaxKind::AssignmentDivision, "/="); }
    Token Operator::AssignmentModulus(const unsigned long i) { return Assignment(i, SyntaxKind::AssignmentModulus, "%="); }

    Token Operator::AssignmentBitwiseAnd(const unsigned long i) { return Assignment(i, SyntaxKind::BitwiseAnd, "&="); }
    Token Operator::AssignmentBitwiseOr(const unsigned long i) { return Assignment(i, SyntaxKind::BitwiseOr, "|="); }
    Token Operator::AssignmentBitwiseXor(const unsigned long i) { return Assignment(i, SyntaxKind::BitwiseXor, "^="); }
    Token Operator::AssignmentRightShift(const unsigned long i) { return Assignment(i, SyntaxKind::RightShift, ">>="); }
    Token Operator::AssignmentLeftShift(const unsigned long i) { return Assignment(i, SyntaxKind::LeftShift, "<<="); }
}
