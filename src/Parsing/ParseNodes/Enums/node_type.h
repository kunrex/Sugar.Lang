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
        Null,
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
        PropertyInitialisation,

        For,
        While,
        DoWhile,

        FunctionCall,
        ConstructorCall,

        FunctionParameters,
        FunctionDeclaration,
        ConstructorDeclaration,

        Print,
        Input,
        Invoke,
        Format,
        Println,
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

        Throw,

        If,
        Else,
        ElseIf,
        IfChain,

        Describer,

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