#ifndef AMBIGUOUS_IMPORT_EXCEPTION_H
#define AMBIGUOUS_IMPORT_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class AmbiguousImportException final : public LogException
    {
        public:
            AmbiguousImportException(const std::string& type1, const std::string& type2, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
