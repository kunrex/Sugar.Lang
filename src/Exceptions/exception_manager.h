#ifndef EXCEPTION_MANAGER_H
#define EXCEPTION_MANAGER_H

#include "../Services/collection.h"
#include "../Services/singleton_service.h"

#include "compile_exception.h"

namespace Exceptions
{
    class ExceptionManager final : public Services::SingletonService<ExceptionManager>, public Services::ConstantCollection<CompileException>
    {
        public:
            ExceptionManager();

            [[nodiscard]] bool LogAllExceptions() const;
    };
}

#endif
