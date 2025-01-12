#include "keyword.h"

using namespace Tokens::Enums;

namespace Tokens
{
    Keyword::Keyword() = default;

    void Keyword::KeywordInit()
    {
        keywordMap["print"] = { SyntaxKind::Print, KeywordType::General };
        keywordMap["input"] = { SyntaxKind::Input, KeywordType::General };
        keywordMap["format"] = { SyntaxKind::Format, KeywordType::General };
        keywordMap["tostring"] = { SyntaxKind::ToString, KeywordType::General };

        keywordMap["let"] = { SyntaxKind::Let, KeywordType::General };

        keywordMap["this"] = { SyntaxKind::This, KeywordType::General };

        keywordMap["get"] = { SyntaxKind::Get, KeywordType::General };
        keywordMap["set"] = { SyntaxKind::Set, KeywordType::General };

        keywordMap["create"] = { SyntaxKind::Create, KeywordType::General };

        keywordMap["throw"] = { SyntaxKind::Throw, KeywordType::General };

        keywordMap["func"] = { SyntaxKind::Func, KeywordType::General };
        keywordMap["action"] = { SyntaxKind::Action, KeywordType::General };
        keywordMap["invoke"] = { SyntaxKind::Invoke, KeywordType::General };
        keywordMap["funcref"] = { SyntaxKind::FuncRef, KeywordType::General };

        keywordMap["as"] = { SyntaxKind::As, KeywordType::General };

        keywordMap["import"] = { SyntaxKind::Import, KeywordType::General };

        keywordMap["enum"] = { SyntaxKind::Enum, KeywordType::DataType };
        keywordMap["class"] = { SyntaxKind::Class, KeywordType::DataType };
        keywordMap["struct"] = { SyntaxKind::Struct, KeywordType::DataType };

        keywordMap["short"] = { SyntaxKind::Short, KeywordType::Type };
        keywordMap["int"] = { SyntaxKind::Int, KeywordType::Type };
        keywordMap["long"] = { SyntaxKind::Long, KeywordType::Type };
        keywordMap["float"] = { SyntaxKind::Float, KeywordType::Type };
        keywordMap["double"] = { SyntaxKind::Double, KeywordType::Type };
        keywordMap["bool"] = { SyntaxKind::Boolean, KeywordType::Type };
        keywordMap["char"] = { SyntaxKind::Character, KeywordType::Type };
        keywordMap["list"] = { SyntaxKind::List, KeywordType::Type };
        keywordMap["tuple"] = { SyntaxKind::Tuple, KeywordType::Type };
        keywordMap["dictionary"] = { SyntaxKind::Dictionary, KeywordType::Type };
        keywordMap["nullable"] = { SyntaxKind::Nullable, KeywordType::Type };
        keywordMap["array"] = { SyntaxKind::Array, KeywordType::Type };
        keywordMap["string"] = { SyntaxKind::String, KeywordType::Type };
        keywordMap["exception"] = { SyntaxKind::Exception, KeywordType::Type };
        keywordMap["object"] = { SyntaxKind::Object, KeywordType::Type };

        keywordMap["void"] = { SyntaxKind::Void, KeywordType::Function };
        keywordMap["indexer"] = { SyntaxKind::Indexer, KeywordType::Function };
        keywordMap["operator"] = { SyntaxKind::Operator, KeywordType::Function };
        keywordMap["explicit"] = { SyntaxKind::Explicit, KeywordType::Function };
        keywordMap["implicit"] = { SyntaxKind::Implicit, KeywordType::Function };
        keywordMap["constructor"] = { SyntaxKind::Static, KeywordType::Function };

        keywordMap["ref"] = { SyntaxKind::Ref, KeywordType::Describer };
        keywordMap["const"] = { SyntaxKind::Const, KeywordType::Describer };
        keywordMap["static"] = { SyntaxKind::Static, KeywordType::Describer };
        keywordMap["public"] = { SyntaxKind::Public, KeywordType::Describer };
        keywordMap["private"] = { SyntaxKind::Private, KeywordType::Describer };

        keywordMap["do"] = { SyntaxKind::Do, KeywordType::Loop };
        keywordMap["for"] = { SyntaxKind::For, KeywordType::Loop };
        keywordMap["while"] = { SyntaxKind::While, KeywordType::Loop };

        keywordMap["if"] = { SyntaxKind::If, KeywordType::Condition };
        keywordMap["elif"] = { SyntaxKind::Elif, KeywordType::Condition };
        keywordMap["else"] = { SyntaxKind::Else, KeywordType::Condition };

        keywordMap["break"] = { SyntaxKind::Break, KeywordType::Control };
        keywordMap["return"] = { SyntaxKind::Return, KeywordType::Control };
        keywordMap["continue"] = { SyntaxKind::Continue, KeywordType::Control };
    }

    std::optional<Token> Keyword::TryMatchKeyword(const std::string& value, const unsigned long i)
    {
        if (const auto result = keywordMap.find(value); result != keywordMap.end()) {
            return std::make_optional(Token(i, TokenType::Keyword, std::get<0>(result->second), static_cast<short>(std::get<1>(result->second)), result->first));
        }

        return std::nullopt;
    }
}
