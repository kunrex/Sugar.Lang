#ifndef EXCEPTION_MANAGER_H
#define EXCEPTION_MANAGER_H

#include "../Services/collection.h"
#include "../Services/singleton_service.h"

#include "compile_exception.h"

namespace Exceptions
{
    class ExceptionManager final : public Services::SingletonService, public Services::ConstantCollection<CompileException>
    {
        private:
            std::vector<CompileException> exceptions;

        public:
            ExceptionManager();

            static ExceptionManager& Instance();

            [[nodiscard]] bool LogAllExceptions() const;
    };
}

#endif
