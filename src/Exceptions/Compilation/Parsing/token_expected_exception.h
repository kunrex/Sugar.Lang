#ifndef TOKEN_EXPECTED_EXCEPTION_H
#define TOKEN_EXPECTED_EXCEPTION_H

#include "parsing_exception.h"
#include "../../log_exception.h"

namespace Exceptions
{
    class TokenExpectedException final : public ParsingException
    {
        public:
            TokenExpectedException(Tokens::Enums::TokenType expected, const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
            TokenExpectedException(Tokens::Enums::SyntaxKind expected, const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
            TokenExpectedException(Tokens::Enums::SeparatorKind expected, const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
    };
}

#endif
