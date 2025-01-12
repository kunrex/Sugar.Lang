#ifndef TOKEN_H
#define TOKEN_H

#include <variant>
#include <optional>

#include "Enums/token_type.h"
#include "Enums/syntax_kind.h"

#include "../../Services/printable.h"

namespace Tokens
{
    class Token final : public Services::Printable
    {
        protected:
            const unsigned long index;

            const Enums::TokenType type;
            const Enums::SyntaxKind syntaxKind;

            const short metadata;
            const std::variant<long, double, std::string_view> value;

        public:
            static Token Invalid(unsigned long i, std::string value);
            static Token Identifier(unsigned long i, std::string value);

            Token(unsigned long index, Enums::TokenType type, Enums::SyntaxKind syntaxKind, long value);
            Token(unsigned long index, Enums::TokenType type, Enums::SyntaxKind syntaxKind, double value);
            Token(unsigned long index, Enums::TokenType type, Enums::SyntaxKind syntaxKind, std::string value);

            Token(unsigned long index, Enums::TokenType type, Enums::SyntaxKind syntaxKind, short metadata, long value);
            Token(unsigned long index, Enums::TokenType type, Enums::SyntaxKind syntaxKind, short metadata, double value);
            Token(unsigned long index, Enums::TokenType type, Enums::SyntaxKind syntaxKind, short metadata, std::string value);

            [[nodiscard]] unsigned long Index() const;

            [[nodiscard]] Enums::TokenType Type() const;
            [[nodiscard]] Enums::SyntaxKind Kind() const;

            [[nodiscard]] short Metadata() const;

            template <typename TType>
            [[nodiscard]] std::optional<TType> Value() const;

            void Print() const override;
    };
}

#endif
