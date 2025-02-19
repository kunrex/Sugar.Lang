#ifndef VARIABLE_DEFINITION_EXCEPTION_H
#define VARIABLE_DEFINITION_EXCEPTION_H

#include "../../log_exception.h"

namespace Exceptions
{
    class DuplicateVariableDefinitionException final : public LogException
    {
        public:
            DuplicateVariableDefinitionException(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
