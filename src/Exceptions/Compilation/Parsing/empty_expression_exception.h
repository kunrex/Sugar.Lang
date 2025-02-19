#ifndef EMPTY_EXPRESSION_EXCEPTION_H
#define EMPTY_EXPRESSION_EXCEPTION_H

#include "parsing_exception.h"

namespace Exceptions
{
    class EmptyExpressionException final : public ParsingException
    {
        public:
            EmptyExpressionException(const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
    };
}

#endif
