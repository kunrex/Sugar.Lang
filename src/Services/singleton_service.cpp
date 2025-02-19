#include "singleton_service.h"

#include "../Exceptions/exception_manager.h"

#include "../Analysis/Structure/Wrappers/Value/short.h"
#include "../Analysis/Structure/Wrappers/Value/integer.h"
#include "../Analysis/Structure/Wrappers/Value/long.h"
#include "../Analysis/Structure/Wrappers/Value/float.h"
#include "../Analysis/Structure/Wrappers/Value/double.h"
#include "../Analysis/Structure/Wrappers/Value/boolean.h"
#include "../Analysis/Structure/Wrappers/Value/character.h"

#include "../Analysis/Structure/Wrappers/Reference/string.h"
#include "../Analysis/Structure/Wrappers/Reference/object.h"
#include "../Analysis/Structure/Wrappers/Reference/exception.h"
#include "../Analysis/Structure/Wrappers/Reference/math.h"

using namespace Exceptions;

using namespace Analysis::Structure::Wrappers;

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

    template class SingletonService<Short>;
    template class SingletonService<Integer>;
    template class SingletonService<Long>;

    template class SingletonService<Float>;
    template class SingletonService<Double>;

    template class SingletonService<Boolean>;
    template class SingletonService<Character>;
    template class SingletonService<String>;
    template class SingletonService<Object>;
    template class SingletonService<Exception>;
    template class SingletonService<Math>;
}


