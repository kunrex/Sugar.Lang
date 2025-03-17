#ifndef NON_STATIC_REFERENCE_EXCEPTION_H
#define NON_STATIC_REFERENCE_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class NonStaticReferenceException final : public LogException
    {
        public:
            NonStaticReferenceException(const std::string& referenced, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
