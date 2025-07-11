#include <iostream>

#include "token.h"

using namespace Tokens::Enums;

namespace Tokens
{
    Token::Token(const unsigned long index, const TokenType type, const SyntaxKind syntaxKind, const long value) : index(index), type(type), syntaxKind(syntaxKind), metadata(0), value(value)
    { }

    Token::Token(const unsigned long index, const TokenType type, const SyntaxKind syntaxKind, const double value) : index(index), type(type), syntaxKind(syntaxKind), metadata(0), value(value)
    { }

    Token::Token(const unsigned long index, const TokenType type, const SyntaxKind syntaxKind, std::string value) : index(index), type(type), syntaxKind(syntaxKind), metadata(0), value(std::move(value))
    { }

    Token::Token(const unsigned long index, const TokenType type, const SyntaxKind syntaxKind, std::string_view value) : index(index), type(type), syntaxKind(syntaxKind), metadata(0), value(std::move(value))
    { }

    Token::Token(const unsigned long index, const TokenType type, const SyntaxKind syntaxKind, const short metadata, const long value) : index(index), type(type), syntaxKind(syntaxKind), metadata(metadata), value(value)
    { }

    Token::Token(const unsigned long index, const TokenType type, const SyntaxKind syntaxKind, const short metadata, const double value) : index(index), type(type), syntaxKind(syntaxKind), metadata(metadata), value(value)
    { }

    Token::Token(const unsigned long index, const TokenType type, const SyntaxKind syntaxKind, const short metadata, std::string value) : index(index), type(type), syntaxKind(syntaxKind), metadata(metadata), value(std::move(value))
    { }

    Token::Token(const unsigned long index, const TokenType type, const SyntaxKind syntaxKind, const short metadata, std::string_view value) : index(index), type(type), syntaxKind(syntaxKind), metadata(metadata), value(std::move(value))
    { }

    Token Token::Invalid(unsigned long i, std::string value) { return { i, TokenType::Invalid, SyntaxKind::Invalid, std::move(value) }; }
    Token Token::Identifier(unsigned long i, std::string value) { return { i, TokenType::Identifier, SyntaxKind::Identifier, std::move(value) }; }

    unsigned long Token::Index() const { return index; }

    TokenType Token::Type() const { return type; }
    SyntaxKind Token::Kind() const { return syntaxKind; }

    short Token::Metadata() const { return metadata; }

    template <typename TType>
    std::optional<TType> Token::Value() const
    {
        if (const auto v = std::get_if<TType>(&value)) {
            return *v;
        }

        return std::nullopt;
    }

    void Token::Print() const
    {
        std::cout << '[' << Type() << ": ";
        std::visit([](auto&& arg) { std::cout << arg << std::endl; }, value);
        std::cout << "]" << std::endl;
    }

    template std::optional<long> Token::Value() const;
    template std::optional<double> Token::Value() const;
    template std::optional<std::string> Token::Value() const;
}