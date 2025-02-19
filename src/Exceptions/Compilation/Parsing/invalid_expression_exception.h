#ifndef INVALID_EXPRESSION_EXCEPTION_H
#define INVALID_EXPRESSION_EXCEPTION_H

#include "parsing_exception.h"

namespace Exceptions
{
    class InvalidExpressionException final : public ParsingException
    {
        public:
            InvalidExpressionException(const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
    };
}

#endif
