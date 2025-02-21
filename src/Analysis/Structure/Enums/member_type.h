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
        EnumField,

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

        PrintContext,
        InputContext,
        FormatContext,

        ThisContext,
        FieldContext,
        PropertyContext,
        ArrayIndex,
        LocalVariableContext,
        FunctionArgumentContext,

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

        InstanceVoidCall,
        InstanceMethodCall,

        StaticVoidCall,
        StaticMethodCall,

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
