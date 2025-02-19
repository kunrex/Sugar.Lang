#ifndef RETURN_ACCESSIBILITY_EXCEPTION_H
#define RETURN_ACCESSIBILITY_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class ReturnAccessibilityException final : public LogException
    {
        public:
            ReturnAccessibilityException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
