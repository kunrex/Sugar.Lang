#ifndef EXCEPTION_MANAGER_H
#define EXCEPTION_MANAGER_H

#include <vector>

#include "compile_exception.h"

namespace Exceptions
{
    class ExceptionManager final
    {
        private:
            static std::vector<CompileException> exceptions;

        public:
            static void PushException(const CompileException& exception);

            [[nodiscard]] static bool LogAllExceptions();
            [[nodiscard]] static unsigned long ExceptionCount();
    };
}

#endif
