#ifndef GENERIC_ARGUMENT_EXCEPTION_H
#define GENERIC_ARGUMENT_EXCEPTION_H

#include "parsing_exception.h"

namespace Exceptions
{
    class GenericArgumentException final : public ParsingException
    {
        public:
            GenericArgumentException(int argumentCount, const Tokens::Token& token, const Analysis::Structure::SourceFile* source);
    };
}

#endif
