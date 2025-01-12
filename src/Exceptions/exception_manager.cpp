#include "exception_manager.h"

#include <iostream>

namespace Exceptions
{
    ExceptionManager::ExceptionManager() : SingletonService(), ConstantCollection()
    { }

    void ExceptionManager::LogAllExceptions() const
    {
        for (const auto exception: children)
        {
            std::cerr << exception->what() << std::endl;
            std::cout<< std::endl;
        }
    }
}
