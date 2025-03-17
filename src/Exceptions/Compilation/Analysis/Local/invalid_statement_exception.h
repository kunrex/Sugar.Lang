#ifndef INVALID_STATEMENT_EXCEPTION_H
#define INVALID_STATEMENT_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class InvalidStatementException final : public LogException
    {
        public:
            InvalidStatementException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
