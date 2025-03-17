#ifndef OPERATOR_KIND_H
#define OPERATOR_KIND_H

namespace Tokens::Enums
{
    enum class OperatorKind : short
    {
        Addition = 3,
        Subtraction = 5,
        Multiplication,
        Division,
        Modulus = 9,

        BitwiseOr,
        BitwiseAnd,
        BitwiseXor,
        LeftShift,
        RightShift,

        Increment,
        Decrement = 17,
        IncrementPrefix,
        DecrementPrefix,

        Not,
        Plus,
        Minus,
        BitwiseNot,

        Equals,
        NotEquals,
        LesserThan,
        GreaterThan,
        LesserThanEquals,
        GreaterThanEquals,

        Or,
        And,

        Assignment = 4096,

        AssignmentAddition = Assignment | Addition,
        AssignmentSubtraction = Assignment | Subtraction,
        AssignmentMultiplication = Assignment | Multiplication,
        AssignmentDivision = Assignment | Division,
        AssignmentModulus = Assignment | Modulus,

        AssignmentBitwiseOr = Assignment | BitwiseOr,
        AssignmentBitwiseAnd = Assignment | BitwiseAnd,
        AssignmentBitwiseXor = Assignment | BitwiseXor,
        AssignmentLeftShift = Assignment | LeftShift,
        AssignmentRightShift = Assignment | RightShift,
    };

    OperatorKind operator|(const OperatorKind& lhs, const OperatorKind& rhs);
    OperatorKind operator&(const OperatorKind& lhs, const OperatorKind& rhs);
    OperatorKind operator^(const OperatorKind& lhs, const OperatorKind& rhs);
}

#endif
