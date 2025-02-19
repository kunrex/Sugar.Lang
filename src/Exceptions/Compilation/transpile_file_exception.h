#ifndef TRANSPILE_FILE_EXCEPTION_H
#define TRANSPILE_FILE_EXCEPTION_H

#include "../compile_exception.h"

namespace Exceptions
{
    class TranspileFileException final : public CompileException
    {
        public:
            explicit TranspileFileException(const std::string& path);
    };
}

#endif
