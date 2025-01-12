#ifndef INVALID_TOKEN_EXCEPTION_H
#define INVALID_TOKEN_EXCEPTION_H

#include "parsing_exception.h"

namespace Exceptions
{
    class InvalidTokenException final : public ParsingException
    {
        public:
            InvalidTokenException(const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
    };
}

#endif
