#ifndef SOURCE_FILE_EXCEPTION_H
#define SOURCE_FILE_EXCEPTION_H

#include "../compile_exception.h"

namespace Exceptions
{
    class SourceFileException final : public CompileException
    {
        public:
            explicit SourceFileException(std::string path);
    };
}

#endif
