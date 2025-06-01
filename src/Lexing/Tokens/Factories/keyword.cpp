#include "keyword.h"

using namespace Tokens::Enums;

namespace Tokens
{
    Keyword::Keyword() = default;

    std::optional<Token> Keyword::TryMatchKeyword(const std::string& value, const unsigned long i)
    {
        static const std::unordered_map<std::string, std::tuple<SyntaxKind, KeywordType>> keywordMap = {
            { "print",       { SyntaxKind::Print,       KeywordType::General } },
            { "println",     { SyntaxKind::Println,     KeywordType::General } },
            { "input",       { SyntaxKind::Input,       KeywordType::General } },
            { "format",      { SyntaxKind::Format,      KeywordType::General } },
            { "tostring",    { SyntaxKind::ToString,    KeywordType::General } },
            { "let",         { SyntaxKind::Let,         KeywordType::General } },
            { "this",        { SyntaxKind::This,        KeywordType::General } },
            { "get",         { SyntaxKind::Get,         KeywordType::General } },
            { "set",         { SyntaxKind::Set,         KeywordType::General } },
            { "create",      { SyntaxKind::Create,      KeywordType::General } },
            { "throw",       { SyntaxKind::Throw,       KeywordType::General } },
            { "invoke",      { SyntaxKind::Invoke,      KeywordType::General } },
            { "funcref",     { SyntaxKind::FuncRef,     KeywordType::General } },
            { "as",          { SyntaxKind::As,          KeywordType::General } },
            { "import",      { SyntaxKind::Import,      KeywordType::General } },

            { "enum",        { SyntaxKind::Enum,        KeywordType::DataType } },
            { "class",       { SyntaxKind::Class,       KeywordType::DataType } },
            { "struct",      { SyntaxKind::Struct,      KeywordType::DataType } },

            { "short",       { SyntaxKind::Short,       KeywordType::Type } },
            { "int",         { SyntaxKind::Int,         KeywordType::Type } },
            { "long",        { SyntaxKind::Long,        KeywordType::Type } },
            { "float",       { SyntaxKind::Float,       KeywordType::Type } },
            { "double",      { SyntaxKind::Double,      KeywordType::Type } },
            { "bool",        { SyntaxKind::Boolean,     KeywordType::Type } },
            { "char",        { SyntaxKind::Character,   KeywordType::Type } },
            { "func",        { SyntaxKind::Func,        KeywordType::Type } },
            { "action",      { SyntaxKind::Action,      KeywordType::Type } },
            { "array",       { SyntaxKind::Array,       KeywordType::Type } },
            { "list",        { SyntaxKind::List,        KeywordType::Type } },
            { "tuple",       { SyntaxKind::Tuple,       KeywordType::Type } },
            { "dictionary",  { SyntaxKind::Dictionary,  KeywordType::Type } },
            { "math",        { SyntaxKind::Math,        KeywordType::Type } },
            { "string",      { SyntaxKind::String,      KeywordType::Type } },
            { "exception",   { SyntaxKind::Exception,   KeywordType::Type } },
            { "nullable",    { SyntaxKind::Nullable,    KeywordType::Type } },
            { "object",      { SyntaxKind::Object,      KeywordType::Type } },

            { "void",        { SyntaxKind::Void,        KeywordType::Function } },
            { "indexer",     { SyntaxKind::Indexer,     KeywordType::Function } },
            { "operator",    { SyntaxKind::Operator,    KeywordType::Function } },
            { "explicit",    { SyntaxKind::Explicit,    KeywordType::Function } },
            { "implicit",    { SyntaxKind::Implicit,    KeywordType::Function } },
            { "constructor", { SyntaxKind::Constructor, KeywordType::Function } },

            { "ref",         { SyntaxKind::Ref,         KeywordType::Describer } },
            { "const",       { SyntaxKind::Const,       KeywordType::Describer } },
            { "static",      { SyntaxKind::Static,      KeywordType::Describer } },
            { "public",      { SyntaxKind::Public,      KeywordType::Describer } },
            { "private",     { SyntaxKind::Private,     KeywordType::Describer } },
            { "constexpr",   { SyntaxKind::Constexpr,   KeywordType::Describer } },
            { "entrypoint",  { SyntaxKind::Entrypoint,  KeywordType::Describer } },

            { "copy",        { SyntaxKind::Copy,        KeywordType::General } },

            { "do",          { SyntaxKind::Do,          KeywordType::Loop } },
            { "for",         { SyntaxKind::For,         KeywordType::Loop } },
            { "while",       { SyntaxKind::While,       KeywordType::Loop } },

            { "if",          { SyntaxKind::If,          KeywordType::Condition } },
            { "elif",        { SyntaxKind::Elif,        KeywordType::Condition } },
            { "else",        { SyntaxKind::Else,        KeywordType::Condition } },

            { "break",       { SyntaxKind::Break,       KeywordType::Control } },
            { "return",      { SyntaxKind::Return,      KeywordType::Control } },
            { "continue",    { SyntaxKind::Continue,    KeywordType::Control } },
        };

        if (const auto result = keywordMap.find(value); result != keywordMap.end()) {
            return std::make_optional(Token(i, TokenType::Keyword, std::get<0>(result->second), static_cast<short>(std::get<1>(result->second)), result->first));
        }

        return std::nullopt;
    }
}
