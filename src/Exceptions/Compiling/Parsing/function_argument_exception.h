#ifndef FUNCTION_ARGUMENT_EXCEPTION_H
#define FUNCTION_ARGUMENT_EXCEPTION_H

#include "parsing_exception.h"

namespace Exceptions
{
    class FunctionArgumentException final : public ParsingException
    {
        public:
            FunctionArgumentException(int argumentCount, const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
    };
}

#endif
