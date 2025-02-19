#ifndef TYPE_EXCEPTION_H
#define TYPE_EXCEPTION_H

#include "../../log_exception.h"

namespace Exceptions
{
    class TypeNotFoundException final : public LogException
    {
        public:
            TypeNotFoundException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };

    class InvalidTypeException final : public LogException
    {
        public:
            InvalidTypeException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
