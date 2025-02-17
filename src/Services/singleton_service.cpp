#include "singleton_service.h"

#include "../Exceptions/exception_manager.h"

using namespace Exceptions;

namespace Services
{
    template <class TSingleton>
    SingletonService<TSingleton>::SingletonService() = default;

    template <class TSingleton>
    TSingleton& SingletonService<TSingleton>::Instance()
    {
        static TSingleton instance;
        return instance;
    }

    template <class TSingleton>
    SingletonService<TSingleton>::~SingletonService() = default;

    template class SingletonService<ExceptionManager>;
}


