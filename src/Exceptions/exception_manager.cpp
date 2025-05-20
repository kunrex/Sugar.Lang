#include "exception_manager.h"

#include <iostream>

namespace Exceptions
{
    ExceptionManager::ExceptionManager() : SingletonService(), ConstantCollection()
    { }

    ExceptionManager& ExceptionManager::Instance()
    {
        static ExceptionManager instance;
        return instance;
    }

    bool ExceptionManager::LogAllExceptions() const
    {
        if (children.empty())
            return false;

        for (const auto exception: children)
        {
            std::cerr << exception->what() << std::endl;
            std::cout << std::endl;
        }

        return true;
    }
}
