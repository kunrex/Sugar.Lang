#ifndef INVALID_CHARACTER_EXCEPTION_H
#define INVALID_CHARACTER_EXCEPTION_H

#include "../../log_exception.h"

namespace Exceptions
{
    class InvalidCharacterException final : public LogException
    {
        public:
            explicit InvalidCharacterException(char c, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
