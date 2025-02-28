#ifndef MEMBER_TYPE_H
#define MEMBER_TYPE_H

namespace Analysis::Structure::Enums
{
    enum class MemberType : long
    {
        Enum,
        Class,
        ValueType,

        Field,

        Property,
        BuiltInProperty,

        Indexer,
        BuiltInIndexer,

        VoidDefinition,
        MethodDefinition,
        BuiltInDefinition,

        BuiltInCast,
        ImplicitCast,
        ExplicitCast,

        BuiltInOperation,
        OperatorOverload,

        Constructor,
        BuiltInConstructor,

        LocalVariable,
        FunctionParameter,

        For,
        While,
        DoWhile,

        RefContext,
        CopyContext,
        PrintContext,
        InputContext,
        InvokeContext,
        FormatContext,
        FuncRefContext,
        FormatSingleContext,
        FormatDoubleContext,

        ThisContext,
        FieldContext,
        PropertyContext,
        ArrayIndex,
        LocalVariableContext,
        FunctionArgumentContext,
        FunctionArgumentAddressContext,

        BoxCast,
        UnboxCast,
        CastClass,
        CastBuiltIn,
        DefinedCast,

        FunctionCallContext,
        OverloadedIndexerContext,

        SingleReference,

        Dot,
        AssignmentOperation,

        OperationBuiltIn,
        OperationOverload,

        Invalid

        UnaryExpression,
        BinaryExpression,

        DefinedIndexerExpression,

        StaticReferenceContext,

        Scope,
        Return,
        BranchJump,

        Constant,
    };
}

#endif
