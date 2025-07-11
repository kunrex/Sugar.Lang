#ifndef MEMBER_TYPE_H
#define MEMBER_TYPE_H

namespace Analysis::Structure::Enums
{
    enum class MemberType : short
    {
        Enum,
        Class,
        ValueType,

        Field,
        ConstantField,

        Property,
        BuiltInProperty,

        Indexer,
        BuiltInIndexer,

        VoidDefinition,
        MethodDefinition,
        BuiltInDefinition,

        CastOverload,
        GeneratedCast,

        OperatorOverload,
        GeneratedOverload,

        Constructor,
        GeneratedConstructor,

        LocalVariable,
        FunctionParameter,

        Throw,
        Scope,
        Return,
        BranchJump,

        ConstantContext,
        NullConstantContext,

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
        LocalVariableContext,
        FunctionParameterContext,

        FunctionCallContext,
        ConstructorCallContext,
        CollectorConstructorCallContext,

        StaticReferenceContext,

        DotExpression,

        IndexerExpression,

        CastExpression,
        UnaryExpression,
        BinaryExpression,
        TernaryExpression,
        AssignmentExpression,
        GeneratedAssignmentExpression,

        PopExpression,
        DuplicateExpression,

        Invalid,
    };
}

#endif
