#ifndef ACCESSOR_BODY_EXCEPTION_H
#define ACCESSOR_BODY_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class AccessorBodyException final : public LogException
    {
        public:
            AccessorBodyException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
