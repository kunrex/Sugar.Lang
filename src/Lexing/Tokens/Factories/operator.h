#ifndef OPERATOR_H
#define OPERATOR_H

#include <tuple>

#include "../token.h"

namespace Tokens
{
    class Operator final
    {
        private:
            Operator();

            static Token Unary(unsigned long index, Enums::SyntaxKind syntaxKind, const std::string& value, bool leftAssociative, int precedence);
            static Token Binary(unsigned long index, Enums::SyntaxKind syntaxKind, const std::string& value, int precedence);
            static Token Assignment(unsigned long index, Enums::SyntaxKind syntaxKind, const std::string& value);

        public:
            static std::tuple<bool, int> DecodeMetadata(const Token& token);
            static short EncodeMetadata(bool leftAssociative, int precedence);

            static std::optional<Enums::SyntaxKind> IsAssignment(Enums::SyntaxKind kind);

            static Token Addition(unsigned long i);
            static Token Subtraction(unsigned long i);

            static Token Multiplication(unsigned long i);
            static Token Division(unsigned long i);
            static Token Modulus(unsigned long i);

            static Token And(unsigned long i);
            static Token Or(unsigned long i);

            static Token BitwiseAnd(unsigned long i);
            static Token BitwiseOr(unsigned long i);
            static Token BitwiseXor(unsigned long i);
            static Token RightShift(unsigned long i);
            static Token LeftShift(unsigned long i);

            static Token Equals(unsigned long i);
            static Token NotEquals(unsigned long i);
            static Token LesserThan(unsigned long i);
            static Token GreaterThan(unsigned long i);
            static Token LesserThanEquals(unsigned long i);
            static Token GreaterThanEquals(unsigned long i);

            static Token As(unsigned long i);

            static Token Increment(unsigned long i);
            static Token Decrement(unsigned long i);

            static Token IncrementPrefix(unsigned long i);
            static Token DecrementPrefix(unsigned long i);

            static Token Not(unsigned long i);
            static Token Plus(unsigned long i);
            static Token Minus(unsigned long i);
            static Token BitwiseNot(unsigned long i);

            static Token Assignment(unsigned long i);

            static Token AssignmentAddition(unsigned long i);
            static Token AssignmentSubtraction(unsigned long i);

            static Token AssignmentMultiplication(unsigned long i);
            static Token AssignmentDivision(unsigned long i);
            static Token AssignmentModulus(unsigned long i);

            static Token AssignmentBitwiseAnd(unsigned long i);
            static Token AssignmentBitwiseOr(unsigned long i);
            static Token AssignmentBitwiseXor(unsigned long i);
            static Token AssignmentRightShift(unsigned long i);
            static Token AssignmentLeftShift(unsigned long i);
    };
}

#endif
