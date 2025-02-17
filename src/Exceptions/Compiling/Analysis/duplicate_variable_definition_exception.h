#ifndef DUPLICATE_VARIABLE_DEFINITION_EXCEPTION_H
#define DUPLICATE_VARIABLE_DEFINITION_EXCEPTION_H

#include "../../log_exception.h"

namespace Exceptions
{
    class InvalidVariableException final : public LogException
    {
        public:
            InvalidVariableException(const std::string& name, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
