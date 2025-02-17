#ifndef SINGLETON_SERVICE_H
#define SINGLETON_SERVICE_H

namespace Services
{
    template <class TSingleton>
    class SingletonService
    {
        protected:
            SingletonService();
            virtual ~SingletonService();

        public:
            static TSingleton& Instance();

            SingletonService(const SingletonService&) = delete;
            SingletonService& operator=(const SingletonService&) = delete;
            SingletonService(SingletonService&&) = delete;
            SingletonService& operator=(SingletonService&&) = delete;
    };

    class SingletonCollection
    {
        protected:
            SingletonCollection();
            virtual ~SingletonCollection();

        public:
            SingletonCollection(const SingletonCollection&) = delete;
            SingletonCollection& operator=(const SingletonCollection&) = delete;
            SingletonCollection(SingletonCollection&&) = delete;
            SingletonCollection& operator=(SingletonCollection&&) = delete;
    };
}

#endif
