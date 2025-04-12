#ifndef SINGLETON_SERVICE_H
#define SINGLETON_SERVICE_H

namespace Services
{
    class SingletonService
    {
        protected:
            SingletonService() = default;
            virtual ~SingletonService() = default;

        public:
            SingletonService(const SingletonService&) = delete;
            SingletonService& operator=(const SingletonService&) = delete;
            SingletonService(SingletonService&&) = delete;
            SingletonService& operator=(SingletonService&&) = delete;
    };
}

#endif
