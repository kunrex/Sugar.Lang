#ifndef INVALID_IMPORT_PATH_EXCEPTION_H
#define INVALID_IMPORT_PATH_EXCEPTION_H

#include "../../../log_exception.h"

namespace Exceptions
{
    class InvalidImportPathException final : public LogException
    {
        public:
            InvalidImportPathException(const std::string& path, unsigned long index, const Analysis::Structure::SourceFile* source);
    };
}

#endif
