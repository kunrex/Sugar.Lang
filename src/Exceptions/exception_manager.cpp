#include "exception_manager.h"

#include <iostream>

namespace Exceptions
{
    std::vector<CompileException> ExceptionManager::exceptions;

    void ExceptionManager::PushException(const CompileException& exception)
    {
        exceptions.emplace_back(exception);
    }

    bool ExceptionManager::LogAllExceptions()
    {
        if (exceptions.empty())
            return false;

        for (const auto& exception: exceptions)
        {
            std::cerr << exception.what() << std::endl;
            std::cout << std::endl;
        }

        return true;
    }

    unsigned long ExceptionManager::ExceptionCount() { return exceptions.size(); }
}
