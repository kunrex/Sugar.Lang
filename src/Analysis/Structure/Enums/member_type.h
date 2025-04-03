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
        EnumField,
        ConstantField,

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

        Throw,
        Scope,
        Return,
        BranchJump,

        ConstantContext,

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
        CollectorConstructorCallContext,

        StaticReferenceContext,

        DotExpression,

        IndexerExpression,

        CastExpression,
        UnaryExpression,
        BinaryExpression,
        TernaryExpression,
        AssignmentExpression,

        Invalid,
    };
}

#endif
