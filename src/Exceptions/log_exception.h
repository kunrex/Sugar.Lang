#ifndef LOG_EXCEPTION_H
#define LOG_EXCEPTION_H

#include "compile_exception.h"
#include "../Analysis/Structure/source_file.h"

namespace Exceptions
{
    class LogException : public CompileException
    {
        private:
            const unsigned long index;
            const std::string sourcePath;

        public:
            LogException(const std::string& message, unsigned long index, const Analysis::Structure::SourceFile* source);

            [[nodiscard]] const char* what() const noexcept override;
    };
}

#endif
