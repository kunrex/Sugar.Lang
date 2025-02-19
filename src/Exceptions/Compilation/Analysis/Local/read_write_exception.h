#ifndef READ_WRITE_EXCEPTION_H
#define READ_WRITE_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class ReadException final : public LogException
    {
        public:
            ReadException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };

    class WriteException final : public LogException
    {
        public:
            WriteException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
