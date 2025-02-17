#ifndef STATIC_BINDING_EXCEPTION_H
#define STATIC_BINDING_EXCEPTION_H

#include "../../log_exception.h"

namespace Exceptions
{
    class StaticBindingException final : public LogException
    {
        public:
            StaticBindingException(const std::string& name, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
