#ifndef SYNTAX_KIND_H
#define SYNTAX_KIND_H

#include <string>

#include "operator_kind.h"
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

        Addition = static_cast<short>(OperatorKind::Addition),
        Subtraction = static_cast<short>(OperatorKind::Subtraction),
        Multiplication = static_cast<short>(OperatorKind::Multiplication),
        Division = static_cast<short>(OperatorKind::Division),
        Modulus = static_cast<short>(OperatorKind::Modulus),

        LeftShift = static_cast<short>(OperatorKind::LeftShift),
        RightShift = static_cast<short>(OperatorKind::RightShift),
        BitwiseOr = static_cast<short>(OperatorKind::BitwiseOr),
        BitwiseAnd = static_cast<short>(OperatorKind::BitwiseAnd),
        BitwiseXor = static_cast<short>(OperatorKind::BitwiseXor),

        Increment = static_cast<short>(OperatorKind::Increment),
        Decrement = static_cast<short>(OperatorKind::Decrement),
        IncrementPrefix = static_cast<short>(OperatorKind::IncrementPrefix),
        DecrementPrefix = static_cast<short>(OperatorKind::DecrementPrefix),

        Not = static_cast<short>(OperatorKind::Not),
        Plus = static_cast<short>(OperatorKind::Plus),
        Minus = static_cast<short>(OperatorKind::Minus),
        BitwiseNot = static_cast<short>(OperatorKind::BitwiseNot),

        Equals = static_cast<short>(OperatorKind::Equals),
        NotEquals = static_cast<short>(OperatorKind::NotEquals),
        LesserThan = static_cast<short>(OperatorKind::LesserThan),
        GreaterThan = static_cast<short>(OperatorKind::GreaterThan),
        LesserThanEquals = static_cast<short>(OperatorKind::LesserThanEquals),
        GreaterThanEquals = static_cast<short>(OperatorKind::GreaterThanEquals),

        Or = static_cast<short>(OperatorKind::Or),
        And = static_cast<short>(OperatorKind::And),

        Assignment = static_cast<short>(OperatorKind::Assignment),

        AssignmentAddition = static_cast<short>(OperatorKind::AssignmentAddition),
        AssignmentSubtraction = static_cast<short>(OperatorKind::AssignmentSubtraction),
        AssignmentMultiplication = static_cast<short>(OperatorKind::AssignmentMultiplication),
        AssignmentDivision = static_cast<short>(OperatorKind::AssignmentDivision),
        AssignmentModulus = static_cast<short>(OperatorKind::AssignmentModulus),

        AssignmentBitwiseOr = static_cast<short>(OperatorKind::AssignmentBitwiseOr),
        AssignmentBitwiseAnd = static_cast<short>(OperatorKind::AssignmentBitwiseAnd),
        AssignmentBitwiseXor = static_cast<short>(OperatorKind::AssignmentBitwiseXor),
        AssignmentBitwiseLeftShift = static_cast<short>(OperatorKind::AssignmentLeftShift),
        AssignmentBitwiseRightShift = static_cast<short>(OperatorKind::AssignmentRightShift),

        Short = static_cast<short>(TypeKind::Short),
        Int = static_cast<short>(TypeKind::Int),
        Long = static_cast<short>(TypeKind::Long),

        Float = static_cast<short>(TypeKind::Float),
        Double = static_cast<short>(TypeKind::Double),

        Boolean = static_cast<short>(TypeKind::Boolean),
        Character = static_cast<short>(TypeKind::Character),

        Array = static_cast<short>(TypeKind::Array),
        List = static_cast<short>(TypeKind::List),
        Dictionary = static_cast<short>(TypeKind::Dictionary),
        Tuple = static_cast<short>(TypeKind::Tuple),

        Func = static_cast<short>(TypeKind::Func),
        Action = static_cast<short>(TypeKind::Action),

        Nullable = static_cast<short>(TypeKind::Nullable),

        Math = static_cast<short>(TypeKind::Math),
        String = static_cast<short>(TypeKind::String),
        Exception = static_cast<short>(TypeKind::Exception),

        Object = static_cast<short>(TypeKind::Object),

        Constant = 51,
        Identifier,

        Copy,
        Print,
        Input,
        Format,
        Println,

        Let,

        This,

        Get,
        Set,

        Throw,
        Create,

        Invoke = 65,
        FuncRef,

        Enum,
        Class,
        Struct,

        Void,
        Indexer,
        Operator,
        Implicit,
        Explicit,
        ToString,
        Constructor,

        Ref,
        Const,
        Static,
        Public,
        Private,
        Constexpr,
        Entrypoint,

        Do,
        For,
        While,

        If,
        Else,
        Elif,

        Break,
        Return,
        Continue,

        True,
        False,

        As,

        Null,

        Import,

        Invalid,
    };

    std::string ToString(const SyntaxKind& syntaxKind);
    std::ostream& operator << (std::ostream& os, const SyntaxKind& dt);
}

#endif
