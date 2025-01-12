#ifndef EXCEPTION_MANAGER_H
#define EXCEPTION_MANAGER_H

#include "compile_exception.h"
#include "../Services/collection.h"
#include "../Services/singleton_service.h"

namespace Exceptions
{
    class ExceptionManager final : public Services::SingletonService<ExceptionManager>, public Services::ConstantCollection<CompileException>
    {
        public:
            ExceptionManager();

            void LogAllExceptions() const;
    };
}

#endif
