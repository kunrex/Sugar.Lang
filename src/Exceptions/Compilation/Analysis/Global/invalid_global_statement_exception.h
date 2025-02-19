#ifndef INVALID_GLOBAL_STATEMENT_EXCEPTION_H
#define INVALID_GLOBAL_STATEMENT_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class InvalidGlobalStatementException final : public LogException
    {
        public:
            InvalidGlobalStatementException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
