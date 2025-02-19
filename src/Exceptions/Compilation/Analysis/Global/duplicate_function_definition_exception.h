#ifndef DUPLICATE_FUNCTION_DEFINITION_EXCEPTION_H
#define DUPLICATE_FUNCTION_DEFINITION_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class DuplicateFunctionDefinition final : public LogException
    {
        public:
            DuplicateFunctionDefinition(unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
