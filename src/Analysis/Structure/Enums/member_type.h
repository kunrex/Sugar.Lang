#ifndef MEMBER_TYPE_H
#define MEMBER_TYPE_H

namespace Analysis::Structure::Enums
{
    enum class MemberType : long
    {
        Enum,
        Class,
        Struct,

        GlobalVariable,

        PropertyGet,
        PropertySet,
        PropertyGetSet,

        VoidDefinition,
        FunctionDefinition,

        BuiltInCast,
        ImplicitCast,
        ExplicitCast,

        BuiltInOperator,
        OperatorOverload,

        Constructor,
        Destructor,

        PrintContext,
        InputContext,
        FormatContext,

        ThisContext,
        FieldContext,
        PropertyContext,
        ArrayIndex,
        LocalVariableContext,
        FunctionArgumentContext,

        Box,
        Unbox,
        CastClass,
        CastBuiltIn,
        CastOverload,

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
    };
}

#endif
