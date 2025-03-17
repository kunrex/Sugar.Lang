#ifndef ACCESSIBILITY_EXCEPTION_H
#define ACCESSIBILITY_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class AccessibilityException final : public LogException
    {
        public:
            AccessibilityException(const std::string& member, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
