#ifndef DUPLICATE_STRUCTURE_DEFINITION_EXCEPTION_H
#define DUPLICATE_STRUCTURE_DEFINITION_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class DuplicateStructureDefinitionException final : public LogException
    {
        public:
            DuplicateStructureDefinitionException(const std::string& name, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
