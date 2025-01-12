#ifndef NODE_TYPE_H
#define NODE_TYPE_H

namespace ParseNodes::Enums
{
    enum class NodeType : short
    {
        Empty,
        Scope,

        Constant,
        Identifier,
        StatementCollection,

        This,
        Generic,

        VoidType,
        FuncType,
        ListType,
        ArrayType,
        TupleType,
        ActionType,
        CreatedType,
        BuiltInType,
        NullableType,
        AnonymousType,
        DictionaryType,

        Declaration,
        Initialisation,
        CompoundCreation,

        Get,
        Set,
        Property,

        For,
        While,
        DoWhile,

        FunctionCall,
        ConstructorCall,

        FunctionParameters,
        FunctionDeclaration,
        ConstructorDeclaration,
        DestructorDeclaration,

        Print,
        Input,
        Invoke,
        Format,
        FuncRef,
        ToString,

        Dot,
        Cast,
        Unary,
        Binary,
        Bracket,
        Indexer,
        Ternary,
        Expression,

        Enum,
        Class,
        Struct,

        Break,
        Return,
        Continue,

        If,
        Else,
        ElseIf,
        IfChain,

        Describer,

        Try,
        Catch,
        Throw,
        Finally,

        OperatorOverload,
        IndexerDeclaration,
        ImplicitDeclaration,
        ExplicitDeclaration,

        Import,

        Source,
        Invalid,
    };
}

#endif