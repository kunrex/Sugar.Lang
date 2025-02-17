#ifndef SYNTAX_KIND_H
#define SYNTAX_KIND_H

#include <iostream>

#include "type_kind.h"
#include "separator_kind.h"

namespace Tokens::Enums
{
    enum class SyntaxKind : short
    {
        Dot = static_cast<short>(SeparatorKind::Dot),
        Comma = static_cast<short>(SeparatorKind::Comma),

        Colon = static_cast<short>(SeparatorKind::Colon),
        Semicolon = static_cast<short>(SeparatorKind::Semicolon),

        QuestionMark = static_cast<short>(SeparatorKind::QuestionMark),

        OpenBracket = static_cast<short>(SeparatorKind::OpenBracket),
        CloseBracket = static_cast<short>(SeparatorKind::CloseBracket),

        BoxOpenBracket = static_cast<short>(SeparatorKind::BoxOpenBracket),
        BoxCloseBracket = static_cast<short>(SeparatorKind::BoxCloseBracket),

        FlowerOpenBracket = static_cast<short>(SeparatorKind::FlowerOpenBracket),
        FlowerCloseBracket = static_cast<short>(SeparatorKind::FlowerCloseBracket),

        Constant = 3,
        Identifier = 5,

        Print = 6,
        Input = 7,
        Format = 9,
        Println = 112,

        Let = 10,

        This = 12,

        Get = 13,
        Set = 14,

        Create = 15,

        Throw = 19,

        Func = 21,
        Action = 22,
        Invoke = 23,
        FuncRef = 24,

        Enum = 25,
        Class = 26,
        Struct = 27,

        Void = 28,
        Indexer = 29,
        Operator = 31,
        Implicit = 33,
        Explicit = 34,
        ToString = 35,
        Constructor = 37,

        Ref = 38,
        Const = 39,
        Static = 40,
        Public = 41,
        Private = 42,

        Do = 43,
        For = 44,
        While = 45,

        If = 46,
        Else = 47,
        Elif = 48,

        Break = 49,
        Return = 50,
        Continue = 51,

        True = 52,
        False = 53,

        Addition = 54,
        Subtraction = 55,
        Multiplication = 56,
        Division = 57,
        Modulus = 58,

        LeftShift = 59,
        RightShift = 60,
        BitwiseOr = 61,
        BitwiseAnd = 62,
        BitwiseXor = 63,

        Increment = 65,
        Decrement = 66,
        IncrementPrefix = 67,
        DecrementPrefix = 68,

        Not = 69,
        Plus = 70,
        Minus = 71,
        BitwiseNot = 72,

        Equals = 73,
        NotEquals = 74,
        LesserThan = 75,
        GreaterThan = 76,
        LesserThanEquals = 77,
        GreaterThanEquals = 78,

        Or = 79,
        And = 80,

        Assignment = 81,

        AssignmentAddition = 82,
        AssignmentSubtraction = 83,
        AssignmentMultiplication = 84,
        AssignmentDivision = 85,
        AssignmentModulus = 86,

        AssignmentBitwiseOr = 87,
        AssignmentBitwiseAnd = 88,
        AssignmentBitwiseXor = 89,
        AssignmentBitwiseLeftShift = 90,
        AssignmentBitwiseRightShift = 91,

        As = 92,

        Null = 93,

        Import = 95,

        Invalid = 96,

        Short = static_cast<short>(TypeKind::Short),
        Int = static_cast<short>(TypeKind::Int),
        Long = static_cast<short>(TypeKind::Long),

        Float = static_cast<short>(TypeKind::Float),
        Double = static_cast<short>(TypeKind::Double),

        Boolean = static_cast<short>(TypeKind::Boolean),
        Character = static_cast<short>(TypeKind::Character),

        String = static_cast<short>(TypeKind::String),
        Object = static_cast<short>(TypeKind::Object),

        Array = static_cast<short>(TypeKind::Array),
        List = static_cast<short>(TypeKind::List),
        Dictionary = static_cast<short>(TypeKind::Dictionary),
        Tuple = static_cast<short>(TypeKind::Tuple),

        Nullable = static_cast<short>(TypeKind::Nullable),

        Exception = static_cast<short>(TypeKind::Exception),
    };

    std::string ToString(const SyntaxKind& syntaxKind);
    std::ostream& operator << (std::ostream& os, const SyntaxKind& dt);
}

#endif
