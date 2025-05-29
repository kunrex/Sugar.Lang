#ifndef RETURN_VALUE_EXCEPTION_H
#define RETURN_VALUE_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class ReturnValueException final : public LogException
    {
        public:
            ReturnValueException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
