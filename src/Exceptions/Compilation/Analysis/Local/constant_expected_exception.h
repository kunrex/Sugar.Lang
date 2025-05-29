#ifndef CONSTANT_EXPECTED_EXCEPTION_H
#define CONSTANT_EXPECTED_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class ConstantNotFoundException final : public LogException
    {
        public:
            ConstantNotFoundException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
